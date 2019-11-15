#pragma once
#include "BFDynamicMemoryJumper.h"
#include "BFMemoryBlock.h"
#include "MaskInfo.h"
#include "c2bf_typedefs.h"
#include <string>
#include <vector>

class CVarType;

constexpr int MACHINE_MEMORY_SIZE = 20;

class BFMemoryManagerIntegrator {
public:
	static const int MEMORY_JUMPER_NULL_CELL_ADDRESS = 0;
	static const int MEMORY_JUMPER_ITER_CELL_ADDRESS = 1;
	static const int MEMORY_JUMPER_FLAG_CELL_ADDRESS = 2;
	static const int MEMORY_ALLOCATE_FLAG_CELL_ADDRESS = 3;
	static const int MEMORY_ALLOCATE_ALWAYS_NULL_CELL_ADDRESS = 4;
	static const int MEMORY_ALLOCATE_ALWAYS_ONE_CELL_ADDRESS = 5;

	static const int COPY_TEMP_VALUE_CELL_ADDRESS = 6;
	static const int MASKS_SIZE = MACHINE_MEMORY_SIZE/2 - 6;
	static const int MASKS_BEGIN_ADDRESS = 7;
	static const int MASKS_END_ADDRESS = 10;//MACHINE_MEMORY_SIZE/2;
	static const int STATIC_MASKS_BEGIN_ADDRESS = MASKS_BEGIN_ADDRESS;
	static const int STATIC_MASKS_END_ADDRESS = MASKS_END_ADDRESS;
	
	//dynamic masks are off while static masks impl is not tested
	/*static const int DYNAMIC_MASKS_BEGIN_ADDRESS = 701; 
	static const int DYNAMIC_MASKS_END_ADDRESS = 1500; */

	static const int DYNAMIC_MEMORY_BEGIN_ADDRESS = 19;//1501;
	static const int DYNAMIC_MEMORY_END_ADDRESS = 30;

	BFMemoryManagerIntegrator();

	std::string cmdInitialize();
	std::string cmdSetupJumperValues();
	std::string cmdSetupAllocateValues();
	std::string cmdCreate(maskloc_t mask); //allocates memory 
	std::string cmdCreateStructure(const std::vector<CVarType*>& types, const std::vector<maskloc_t>& masks);
	maskloc_t   cmdPreReserveMask(); //gets next mask
	maskloc_t   cmdReserveMaskFor(const MaskInfo& mask_info);
	std::string cmdOperateWithMaskedMemory(maskloc_t mask, const std::string& bf_operations_block);
	std::string cmdJumpToMaskedMemoryWithOffset(maskloc_t mask, unsigned int memory_offset);
	std::string cmdDeleteMemoryByMask(maskloc_t mask);
	std::string cmdStaticJumpToMask(maskloc_t mask);
	std::string cmdStaticCopy(maskloc_t m1, maskloc_t m2);
	std::string cmdStaticMove(maskloc_t m1, maskloc_t m2);
	std::string cmdStaticMakeNull(maskloc_t m);
	std::string cmdMove(maskloc_t src, maskloc_t dest, maskloc_t current);
	std::string cmdCopy(maskloc_t src, maskloc_t dest, maskloc_t current);
	std::string cmdMakeNull();
	std::string cmdMakePositive(unsigned int value);
	std::string cmdMakeNegative(unsigned int value);
	std::string cmdJumpForward(unsigned int n);
	std::string cmdJumpBack(unsigned int n);
	std::string cmdJumpFromTo(memloc_t from, memloc_t to);
	std::string cmdJumpOffset(int n);
	std::string cmdInsideBlockJumpTo(unsigned int offset_position);
	std::string cmdInsideBlockMove(unsigned int src_offset_pos, unsigned int dst_offset_pos);
	std::string cmdInsideBlockCopy(unsigned int src_offset_pos, unsigned int dst_offset_pos);

	unsigned int getMaskLevel(maskloc_t mask);
	BFMemoryBlock* getCurrentMemoryBlock();

	void setStaticCurrentMaskAddress(maskloc_t address);

	void initializeInsideBlockCodeGeneration();
private:
	BFDynamicMemoryJumper dynamic_memory_jumper;
	BFMemoryBlock* current_memory_block;
	std::vector<MaskInfo> masks_info;

	count_t reserved_masks_count;
	unsigned int current_static_mask_address;
	unsigned int current_block_position_offset;

	std::string recursiveAllocate(maskloc_t current_pos, maskloc_t target_mask, maskloc_t current_mask);
};