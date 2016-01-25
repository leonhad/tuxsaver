#include "objectloader.h"

ObjectLoader::ObjectLoader() {
  error = 0;
  listValue = -1;
}

ObjectLoader::~ObjectLoader() {
}
 
bool ObjectLoader::isError() {
  return error;
}

int ObjectLoader::getListValue() {
  return listValue;
}

