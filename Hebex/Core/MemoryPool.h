#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include "Hebex.h"
#include "Utils.h"

namespace Hebex
{
	#define ARENA_ALLOC(arena, Type) new ((arena).Alloc(sizeof(Type))) Type

	void* AllocAligned(size_t size);

	template<typename T>
	T *AllocAligned(size_t count) {
		return (T *)AllocAligned(count * sizeof(T));
	}

	void FreeAligned(void*);

	class alignas(L1_CACHE_LINE_SIZE) MemoryPool{
	public:
		MemoryPool(size_t blockSize = 262144) : mBlockSize(blockSize) {}

		~MemoryPool() {
			FreeAligned(mCurrentBlock);
			for (auto &block : mUsedBlocks) FreeAligned(block.second);
			for (auto &block : mAvailableBlocks) FreeAligned(block.second);
		}

		void* Alloc(size_t nBytes) {
			const int align = alignof(std::max_align_t);
			static_assert(IsPowerOf2(align), "Minium alignment must be a power of tow");
			
			nBytes = (nBytes + align - 1) & (~(align - 1));
			if (mCurrentBlockOffset + nBytes > mCurrentAllocSize) {
				if (mCurrentBlock) {
					mUsedBlocks.push_back(std::make_pair(mCurrentAllocSize, mCurrentBlock));
					mCurrentBlock = nullptr;
					mCurrentAllocSize = 0;
				}

				for (auto iter = mAvailableBlocks.begin(); iter != mAvailableBlocks.end(); ++iter) {
					if (iter->first >= nBytes) {
						mCurrentAllocSize = iter->first;
						mCurrentBlock = iter->second;
						mAvailableBlocks.erase(iter);
						break;
					}
				}
				if (!mCurrentBlock) {
					mCurrentAllocSize = std::max(nBytes, mBlockSize);
					mCurrentBlock = AllocAligned<uint8_t>(mCurrentAllocSize);
				}
				mCurrentBlockOffset = 0;
			}

			void *ret = mCurrentBlock + mCurrentBlockOffset;
			mCurrentBlockOffset += nBytes;

			return ret;
		}

		template <typename T>
		T *Alloc(size_t n = 1, bool runConstructor = true) {
			T *ret = (T *)Alloc(n * sizeof(T));
			if (runConstructor)
				for (size_t i = 0; i < n; ++i) new (&ret[i]) T();
			return ret;
		}

		void Reset() {
			mCurrentBlockOffset = 0;
			mAvailableBlocks.splice(mAvailableBlocks.begin(), mUsedBlocks);
		}

		size_t TotalAllocated() const {
			size_t total = mCurrentAllocSize;
			for (const auto &iter : mUsedBlocks) total += iter.first;
			for (const auto &iter : mAvailableBlocks) total += iter.first;
			return total;
		}

	private:
		MemoryPool(const MemoryPool &) = delete;
		MemoryPool &operator=(const MemoryPool &) = delete;
		const size_t mBlockSize;
		size_t mCurrentBlockOffset = 0, mCurrentAllocSize = 0;
		uint8_t *mCurrentBlock = nullptr;
		std::list<std::pair<size_t, uint8_t *>> mUsedBlocks, mAvailableBlocks;
	};
	
}

#endif