#pragma once
#include <string>
#include <vector>
#include "text.h"
#include "util.h"

class AbcStore
{
public:
  std::vector<TextBlock> data;
  virtual int Save(std::string path) = 0;
};

class NatureStore : public AbcStore
{
public:
  int Save(std::string path);
};

class ConceptStore : public AbcStore
{
public:
  int Save(std::string path);
};

class ExercisesStore : public AbcStore
{
public:
  int Save(std::string path);
};

class TextStore : public AbcStore
{
public:
  int Save(std::string path);
};