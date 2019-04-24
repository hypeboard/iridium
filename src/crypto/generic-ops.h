// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2017-2019, The Iridium developers
// You should have received a copy of the GNU Lesser General Public License
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>
#include <cstring>
#include <functional>

#define CRYPTO_MAKE_COMPARABLE(type) \
namespace Crypto { \
  inline bool operator==(const type &_v1, const type &_v2) { \
    return std::memcmp(&_v1, &_v2, sizeof(type)) == 0; \
  } \
  inline bool operator!=(const type &_v1, const type &_v2) { \
    return std::memcmp(&_v1, &_v2, sizeof(type)) != 0; \
  } \
}

#define CRYPTO_MAKE_HASHABLE(type) \
CRYPTO_MAKE_COMPARABLE(type) \
namespace Crypto { \
  static_assert(sizeof(size_t) <= sizeof(type), "Size of " #type " must be at least that of size_t"); \
  inline size_t hash_value(const type &_v) { \
    return reinterpret_cast<const size_t &>(_v); \
  } \
} \
namespace std { \
  template<> \
  struct hash<Crypto::type> { \
    size_t operator()(const Crypto::type &_v) const { \
      return reinterpret_cast<const size_t &>(_v); \
    } \
  }; \
}
