#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <cstdlib>
#include "root_directory.h"

class FileSystem
{
    using Builder = std::string (*) (const std::string&);

public:
    static std::string getPath(const std::string &path)
    {
        static std::string (*pathBuilder)(std::string const &) = getPathBuilder();
        return (*pathBuilder)(path);
    }

private:
    static std::string const & getRoot()
    {
        static const char *envRoot = getenv("LOGL_ROOT_PATH");
        static const char *givenRoot = (envRoot != nullptr ? envRoot : logl_root);
        static std::string root = (givenRoot != nullptr ? givenRoot : "");
        return root;
    }

    static Builder getPathBuilder()
    {
        if (getRoot() != "")
            return &FileSystem::getPathRelativeRoot;
        else 
            return &FileSystem::getPathRelativeBinary;
    }

    static std::string getPathRelativeRoot(const std::string &path)
    {
        return getRoot() + "/" + path;
    }

    static std::string getPathRelativeBinary(const std::string &path)
    {
        return "../../../" + path;
    }
};

#endif