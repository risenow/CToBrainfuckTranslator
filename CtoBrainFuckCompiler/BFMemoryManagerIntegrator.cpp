#include "stdafx.h"
#include "BFMemoryManagerIntegrator.h"
#include <assert.h>

BFMemoryManagerIntegrator::BFMemoryManagerIntegrator(): reserved_masks_count(10), current_static_mask_address(0), dynamic_memory_jumper("jumper_template.bft"){}

maskloc_t BFMemoryManagerIntegrator::cmdPreReserveMask() {
	return (reserved_masks_count);
}
maskloc_t BFMemoryManagerIntegrator::cmdReserveMaskFor(const MaskInfo& mask_info) {
	masks_info.push_back(mask_info);
	return reserved_masks_count++;
}

//dynamic opers
std::string BFMemoryManagerIntegrator::cmdOperateWithMaskedMemory(maskloc_t mask, const std::string& bf_code_block) {
	std::string result;
	result += cmdStaticCopy(mask, MEMORY_JUMPER_ITER_CELL_ADDRESS);
	result += cmdStaticJumpToMask(MEMORY_JUMPER_FLAG_CELL_ADDRESS);
	result += cmdMakePositive(1); //initialize flag as 1
	result += cmdStaticJumpToMask(0);
	result += dynamic_memory_jumper.jump(bf_code_block + cmdInsideBlockJumpTo(0)); 
	return result;
}

//allocator engine
std::string BFMemoryManagerIntegrator::recursiveAllocate(maskloc_t current_pos, maskloc_t target_mask, maskloc_t current_mask) {
	std::string result;
	maskloc_t local_curr = current_pos;
	maskloc_t alt_local_curr = current_pos;
	
	result += cmdJumpFromTo(local_curr, MEMORY_ALLOCATE_FLAG_CELL_ADDRESS); local_curr = MEMORY_ALLOCATE_FLAG_CELL_ADDRESS;
	result += "[";
	result += cmdJumpFromTo(local_curr, current_mask); local_curr = current_mask;
	result += "[";
	result += cmdCopy(current_mask, target_mask, local_curr);
	if (masks_info.size() > 1)
		for (int i = 0; i < masks_info[current_mask].memory_size; i++)//type->getSize(); i++)
			result += "+";
	result += cmdJumpFromTo(local_curr, MEMORY_ALLOCATE_FLAG_CELL_ADDRESS); alt_local_curr = MEMORY_ALLOCATE_FLAG_CELL_ADDRESS;
	result += "+";
	result += "]";

	//sync main local curr with alternative MAGIC IS HERE
	result += ">";
	result += "[";
	result += cmdJumpFromTo(alt_local_curr, local_curr + 1);
	result += "]";
	result += "<";

	if (masks_info.size() > 1)
		if (masks_info[current_mask - 1].level >= masks_info[target_mask].level - 1)
			result += recursiveAllocate(local_curr, target_mask, current_mask - 1);
	result += cmdJumpFromTo(local_curr, MEMORY_ALLOCATE_ALWAYS_NULL_CELL_ADDRESS);
	result += "]";
	current_static_mask_address = MEMORY_ALLOCATE_ALWAYS_NULL_CELL_ADDRESS;
	return result;
}
//allocator
std::string BFMemoryManagerIntegrator::cmdCreate(maskloc_t mask) {
	if (masks_info.size() == 1) {
		return cmdStaticJumpToMask(mask) + cmdMakePositive(DYNAMIC_MEMORY_BEGIN_ADDRESS);
	}
	return recursiveAllocate(current_static_mask_address, mask, mask - 1);
}

//static opers
std::string BFMemoryManagerIntegrator::cmdStaticJumpToMask(maskloc_t target) {
	std::string result;
	int offset = target - current_static_mask_address;
	current_static_mask_address = target;
	result.resize(abs(offset));
	if (offset > 0) {
		for (int i = 0; i < abs(offset); i++)
			result[i] = '>';
		return result;
	}
	for (int i = 0; i < abs(offset); i++)
		result[i] = '<';
	return result;
}
std::string BFMemoryManagerIntegrator::cmdStaticMove(maskloc_t m1, maskloc_t m2) {
	std::string result;
	result += cmdStaticMakeNull(m2);
	result += cmdStaticJumpToMask(m1);
	result += "[";
	result += cmdStaticJumpToMask(m2);
	result += "+";
	result += cmdStaticJumpToMask(m1);
	result += "-";
	result += "]";
	return result;
}
std::string BFMemoryManagerIntegrator::cmdStaticCopy(maskloc_t m1, maskloc_t m2) {
	std::string result;
	result += cmdStaticMakeNull(m2);
	result += cmdStaticMakeNull(COPY_TEMP_VALUE_CELL_ADDRESS);
	result += cmdStaticJumpToMask(m1);
	result += "[";
	result += cmdStaticJumpToMask(m2);
	result += "+";
	result += cmdStaticJumpToMask(COPY_TEMP_VALUE_CELL_ADDRESS);
	result += "+";
	result += cmdStaticJumpToMask(m1);
	result += "-";
	result += "]";
	result += cmdStaticMove(COPY_TEMP_VALUE_CELL_ADDRESS, m1); //recover m1

	return result;
}
std::string BFMemoryManagerIntegrator::cmdStaticMakeNull(maskloc_t m) {
	std::string result;
	result += cmdStaticJumpToMask(m);
	result += "[-]";
	return result;
}

std::string BFMemoryManagerIntegrator::cmdCopy(maskloc_t src, maskloc_t dest, maskloc_t current) {
	std::string result;
	maskloc_t local_curr = current;

	result += cmdJumpFromTo(local_curr, dest);                         local_curr = dest;
	result += cmdMakeNull();
	result += cmdJumpFromTo(local_curr, COPY_TEMP_VALUE_CELL_ADDRESS); local_curr = COPY_TEMP_VALUE_CELL_ADDRESS;
	result += cmdMakeNull();

	result += cmdJumpFromTo(local_curr, src);                          local_curr = src;
	result += "[";
	result += cmdJumpFromTo(local_curr, dest);                         local_curr = dest;
	result += "+";
	result += cmdJumpFromTo(local_curr, COPY_TEMP_VALUE_CELL_ADDRESS); local_curr = COPY_TEMP_VALUE_CELL_ADDRESS;
	result += "+";
	result += cmdJumpFromTo(local_curr, src);                          local_curr = src;
	result += "-";
	result += "]";

	result += cmdMove(COPY_TEMP_VALUE_CELL_ADDRESS, src, local_curr); //recover source value
	result += cmdJumpFromTo(local_curr, current);
	return result;
}
std::string BFMemoryManagerIntegrator::cmdMove(maskloc_t src, maskloc_t dest, maskloc_t current) {
	std::string result;
	maskloc_t local_curr = current;
	result += cmdJumpFromTo(local_curr, dest); local_curr = dest;
	result += cmdMakeNull();

	result += cmdJumpFromTo(local_curr, src);  local_curr = src;
	result += "[";
	result += cmdJumpFromTo(local_curr, dest); local_curr = dest;
	result += "+";
	result += cmdJumpFromTo(local_curr, src);  local_curr = src;
	result += "-";
	result += "]";

	result += cmdJumpFromTo(local_curr, current);
	return result;
}
std::string BFMemoryManagerIntegrator::cmdMakeNull() {
	return "[-]";
}
std::string BFMemoryManagerIntegrator::cmdMakePositive(unsigned int value) {
	std::string result; 
	//TODO remove + operator usage, replace it by pre reserved size string operations
	result += cmdMakeNull();
	for (int i = 0; i < value; i++)
		result += "+";
	return result;
}
std::string BFMemoryManagerIntegrator::cmdJumpForward(unsigned int n) {
	std::string result;
	result.reserve(n);
	for (int i = 0; i < n; i++)
		result[i] = '>';
	return result;
}
std::string BFMemoryManagerIntegrator::cmdJumpBack(unsigned int n) {
	std::string result;
	result.resize(n);
	for (int i = 0; i < n; i++)
		result[i] = '<';
	return result;
}
std::string BFMemoryManagerIntegrator::cmdJumpFromTo(unsigned int from, unsigned int to) {
	std::string result;
	int offset = to - from;

	result.resize(abs(offset));
	if (offset > 0) {
		for (int i = 0; i < abs(offset); i++)
			result[i] = '>';
		return result;
	}
	for (int i = 0; i < abs(offset); i++)
		result[i] = '<';
	return result;
}
std::string BFMemoryManagerIntegrator::cmdJumpOffset(int n) {
	std::string result;
	int abs_n = abs(n);
	result.resize(abs_n);
	if (n > 0)
		for (int i = 0; i < abs_n; i++)
			result[i] = '>';
	else
		for (int i = 0; i < abs_n; i++)
			result[i] = '<';
	return result;
}

std::string BFMemoryManagerIntegrator::cmdInsideBlockJumpTo(unsigned int offset_position) {
	int offset = offset_position - current_block_position_offset;
	current_block_position_offset = offset_position;
	return cmdJumpOffset(offset);
}
std::string BFMemoryManagerIntegrator::cmdInsideBlockMove(unsigned int src_offset_pos, unsigned int dst_offset_pos) {
	std::string result;
	result += cmdInsideBlockJumpTo(src_offset_pos);
	result += "[";
	result += cmdInsideBlockJumpTo(dst_offset_pos);
	result += "+";
	result += cmdInsideBlockJumpTo(src_offset_pos);
	result += "-";
	result += "]";
	return result;
}
std::string BFMemoryManagerIntegrator::cmdInsideBlockCopy(unsigned int src_offset_pos, unsigned int dst_offset_pos){
	std::string result;
	result += cmdInsideBlockJumpTo(dst_offset_pos);
	result += cmdMakeNull();
	result += cmdInsideBlockJumpTo(current_memory_block->getTempRegisterOffsetPosition());
	result += cmdMakeNull();
	result += cmdInsideBlockJumpTo(src_offset_pos);
	result += "[";
	result += cmdInsideBlockJumpTo(dst_offset_pos);
	result += "+";
	result += cmdInsideBlockJumpTo(current_memory_block->getTempRegisterOffsetPosition());
	result += "+";
	result += cmdInsideBlockJumpTo(src_offset_pos);
	result += "-";
	result += "]";
	result += cmdInsideBlockMove(current_memory_block->getTempRegisterOffsetPosition(), src_offset_pos);
	return result;
}

unsigned int BFMemoryManagerIntegrator::getMaskLevel(maskloc_t mask) {
	assert(mask >= masks_info.size());
	return masks_info[mask].level;
}
void BFMemoryManagerIntegrator::setStaticCurrentMaskAddress(maskloc_t address) {
	current_static_mask_address = address;
}
void BFMemoryManagerIntegrator::initializeInsideBlockCodeGeneration() {
	current_block_position_offset = 0;
}