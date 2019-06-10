#include "store.h"

int NatureStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2File(path + "/nature/" + std::to_string(d.id), d.Dumps());
    }
    return 1;
}

int ConceptStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2File(path + "/concept/" + std::to_string(d.id), d.Dumps());
    }
    return 1;
}

int ExercisesStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2File(path + "/exercises/" + std::to_string(d.id), d.Dumps());
    }
    return 1;
}

int ExampleStore::Save(std::string path)
{
    for (auto d : data){
        WriteString2File(path + "/example/" + std::to_string(d.id), d.Dumps());
    }
    return 1;
}

int TextStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2File(path + "/text/" + std::to_string(d.id), d.Dumps());
    }
    return 1;
}
