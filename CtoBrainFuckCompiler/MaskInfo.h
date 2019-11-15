#pragma once
class CVarType;

struct MaskInfo {
	size_t memory_size;//CVarType* type;
	unsigned int level;

	MaskInfo(size_t size, unsigned int _level):memory_size(size), level(_level) {}
};