#include "store.h"

int NatureStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/nature/" + d.title, d.Dumps());
    }
    return 1;
}

int ConceptStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/concept/" + d.title, d.Dumps());
    }
    return 1;
}

int ExercisesStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/exercises/" + d.title, d.Dumps());
    }
    return 1;
}

int TextStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/text/" + d.title, d.Dumps());
    }
    return 1;
}