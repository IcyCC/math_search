#include "store.h"

int NatureStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/nature/" + d.chapter, d.Dumps());
    }
    return 1;
}

int ConceptStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/concept/" + d.chapter, d.Dumps());
    }
    return 1;
}

int ExercisesStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/exercises/" + d.chapter, d.Dumps());
    }
    return 1;
}

int ExampleStore::Save(std::string path)
{
    for (auto d : data){
        WriteString2FileAppend(path + "/example/" + d.chapter, d.Dumps());
    }
    return 1;
}

int TextStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/text/" + d.chapter, d.Dumps());
    }
    return 1;
}
