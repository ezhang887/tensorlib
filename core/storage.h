#pragma once

#include <cstddef>

class Storage {
private:
  void *data_;
  size_t bytes_;

public:
  Storage() = delete;
  Storage(const Storage &) = delete;
  Storage &operator=(const Storage &other) = delete;

  Storage(size_t bytes, bool clear_memory);
  Storage(Storage &&);
  Storage &operator=(Storage &&other);
  ~Storage();
  void *data() const;
};
