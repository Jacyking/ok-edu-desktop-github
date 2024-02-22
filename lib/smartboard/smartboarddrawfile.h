#pragma once

#include "smartboard.h"

namespace SmartBoard
{

    class DrawFile : public DrawItem
    {
    private:
        size_t _size;
        std::string _name;
        std::string _url;
        std::string _md5;
        std::string _token;
        std::string _contentType;

    public:
        DrawFile();
        DrawFile(const std::string &id, const std::string &name);

        const size_t size() const;
        void setSize(size_t size);

        const std::string &name() const;
        void setName(const std::string &);

        const std::string &url() const;
        void setUrl(const std::string &);

        const std::string &md5() const;
        void setMd5(const std::string &);

        const std::string &token() const;
        void setToken(const std::string &);

        const std::string &contentType() const;
        void setContentType(const std::string &);


    };

}