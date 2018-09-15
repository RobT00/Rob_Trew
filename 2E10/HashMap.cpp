#include "HashMap.h"

HashMap::~HashMap() {
  delete[] _keys;
  delete[] _handlers;
}

#ifndef TEST
void HashMap::add(String key, VoidFunction handler) {
  add(key.c_str(), handler);
}
#endif
void HashMap::add(cstring key, VoidFunction handler) {
  hash_t hash = hashString(key);

  // Allocate new storage
  // The function is not called often, therefore it can reallocate on each call
  hash_t* newKeys = new hash_t[_size + 1];
  VoidFunction* newHandlers = new VoidFunction[_size + 1];

  // Insert new hash and handler, maintaining the ordering
  size_t i = 0;
  for (; i < _size; i++) {
    if (_keys[i] < hash) {
      newKeys[i] = _keys[i];
      newHandlers[i] = _handlers[i];
    } else if (_keys[i] == hash) {
      // If key already exits, simply overwrite the handler
      delete[] newKeys;
      delete[] newHandlers;
      _handlers[i] = handler;
      return;
    } else {
      break;
    }
  }
  newKeys[i] = hash;
  newHandlers[i] = handler;
  for (; i < _size; i++) {
    newKeys[i + 1] = _keys[i];
    newHandlers[i + 1] = _handlers[i];
  }

  // Replace old storage
  delete[] _keys;
  delete[] _handlers;
  _keys = newKeys;
  _handlers = newHandlers;
  _size++;
}

#ifndef TEST
VoidFunction HashMap::get(String key) const {
  return get(key.c_str());
}
#endif
VoidFunction HashMap::get(cstring key) const {
  hash_t hash = hashString(key);
  size_t lo = 0,
       hi = _size,
       mid;
  while (lo < hi) {
    mid = lo + ((hi - lo) >> 1);
    if (_keys[mid] < hash) {
      lo = mid + 1;
    } else if (_keys[mid] == hash) {
      return _handlers[mid];
    } else {
      hi = mid;
    }
  }
  return nullptr;
}

HashMap::hash_t HashMap::hashString(cstring str) {
  hash_t hash = 5381;
  char c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) ^ c;
  }

  return hash;
}
