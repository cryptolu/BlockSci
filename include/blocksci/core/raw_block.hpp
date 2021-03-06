//
//  raw_block.hpp
//  blocksci
//
//  Created by Harry Kalodner on 11/18/17.
//

#ifndef raw_block_hpp
#define raw_block_hpp

#include "bitcoin_uint256.hpp"

#include <blocksci/blocksci_export.h>

namespace blocksci {
    struct BLOCKSCI_EXPORT RawBlock {
        uint32_t firstTxIndex;
        uint32_t numTxes;
        uint32_t height;
        uint256 hash;
        int32_t version;
        uint32_t timestamp;
        uint32_t bits;
        uint256 nonce;
        uint32_t realSize;
        uint32_t baseSize;
        uint64_t coinbaseOffset;
               
        RawBlock(uint32_t firstTxIndex_, uint32_t numTxes_, uint32_t height_, uint256 hash_, int32_t version_, uint32_t timestamp_, uint32_t bits_, uint256 nonce_, uint32_t realSize_, uint32_t baseSize_, uint64_t coinbaseOffset_) : firstTxIndex(firstTxIndex_), numTxes(numTxes_), height(height_), hash(hash_), version(version_), timestamp(timestamp_), bits(bits_), nonce(nonce_), realSize(realSize_), baseSize(baseSize_), coinbaseOffset(coinbaseOffset_) {}
        
        bool operator==(const RawBlock& other) const {
            return firstTxIndex == other.firstTxIndex
            && numTxes == other.numTxes
            && height == other.height
            && hash == other.hash
            && version == other.version
            && timestamp == other.timestamp
            && bits == other.bits
            && nonce == other.nonce
            && coinbaseOffset == other.coinbaseOffset;
        }
    };
} // namespace blocksci

#endif /* raw_block_hpp */