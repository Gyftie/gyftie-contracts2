
#include <algorithm>
#include <array>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <string_view>
#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>

using namespace eosio;
using std::set;
using std::vector;
using std::string;

namespace permissions
{

const char base58_chars[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

bool map_initialized = false;
std::array<int8_t, 256> base58_map{{0}};
auto get_base58_map()
{
  if (!map_initialized)
  {
    for (unsigned i = 0; i < base58_map.size(); ++i)
      base58_map[i] = -1;
    for (unsigned i = 0; i < sizeof(base58_chars); ++i)
      base58_map[base58_chars[i]] = i;
    map_initialized = true;
  }
  return base58_map;
}

template <size_t size>
std::array<uint8_t, size> base58_to_binary(std::string_view s)
{
  // print (" String in to_binary: ", s.data(), "\n");
  std::array<uint8_t, size> result{{0}};
  for (auto &src_digit : s)
  {
    int carry = get_base58_map()[src_digit];
    // print (" Source digit: ", src_digit, "\n");
    // print ( " Carry: ", std::to_string(carry), "\n");
    eosio::check(carry >= 0, "invalid base-58 value");
    for (auto &result_byte : result)
    {
      int x = result_byte * 58 + carry;
      result_byte = x;
      carry = x >> 8;
    }
    eosio::check(!carry, "base-58 value is out of range");
  }
  std::reverse(result.begin(), result.end());
  return result;
}

enum class key_type : uint8_t
{
  k1 = 0,
  r1 = 1,
};

struct public_key
{
  key_type type{};
  std::array<uint8_t, 33> data{};
};

template <typename Key, int suffix_size>
Key string_to_key(std::string_view s, key_type type, const char (&suffix)[suffix_size])
{
  static const auto size = std::tuple_size<decltype(Key::data)>::value;
  auto whole = base58_to_binary<size + 4>(s);
  Key result{type};
  memcpy(result.data.data(), whole.data(), result.data.size());
  return result;
}

public_key string_to_public_key(std::string_view s)
{
  if (s.size() >= 3 && s.substr(0, 3) == "EOS")
  {
    auto whole = base58_to_binary<37>(s.substr(3));
    public_key key{key_type::k1};
    static_assert(whole.size() == key.data.size() + 4, "Error: whole.size() != key.data.size() + 4");
    memcpy(key.data.data(), whole.data(), key.data.size());
    return key;
  }
  else if (s.size() >= 7 && s.substr(0, 7) == "PUB_R1_")
  {
    return string_to_key<public_key>(s.substr(7), key_type::r1, "R1");
  }
  else
  {
    eosio::check(0, "unrecognized public key format");
    return public_key{key_type::k1};
  }
}

struct key_weight
{
  eosio::public_key key;
  uint16_t weight;
};

struct permission_level_weight
{
  permission_level permission;
  uint16_t weight;
};

struct wait_weight
{
  uint32_t wait_sec;
  uint16_t weight;
};

struct authority
{
  uint32_t threshold;
  std::vector<key_weight> keys;
  std::vector<permission_level_weight> accounts;
  std::vector<wait_weight> waits;
};

authority keystring_authority(string key_str)
{
  // Convert string to key type
  const permissions::public_key key = permissions::string_to_public_key(key_str);

  // Setup authority
  authority ret_authority;

  // Array to hold public key
  std::array<char, 33> key_char;

  // Copy key to char array
  std::copy(key.data.begin(), key.data.end(), key_char.begin());

  key_weight kweight{
      .key = {(uint8_t)permissions::key_type::k1, key_char},
      .weight = (uint16_t)1};

  // Authority
  ret_authority.threshold = 1;
  ret_authority.keys = {kweight};
  ret_authority.accounts = {};
  ret_authority.waits = {};

  return ret_authority;
}

} // namespace permissions