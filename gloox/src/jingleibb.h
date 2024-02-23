/*
Copyright (c) 2022 船山科技 chuanshantech.com
OkEDU-Classroom is licensed under Mulan PubL v2.
You can use this software according to the terms and conditions of the Mulan PubL v2.
You may obtain a copy of Mulan PubL v2 at:
         http://license.coscl.org.cn/MulanPubL-2.0
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PubL v2 for more details.

Mulan Public License，Version 2

Mulan Public License，Version 2 (Mulan PubL v2)

May 2021 http://license.coscl.org.cn/MulanPubL-2.0

Your reproduction, use, modification and Distribution of the Contribution shall be subject to Mulan Public License, Version 2 (this License) with following terms and conditions:
*/


#ifndef JINGLE_IBB_H__
#define JINGLE_IBB_H__

#include "jingleplugin.h"
#include "inbandbytestream.h"
#include <string>
#include <list>

namespace gloox {

    class Tag;

    namespace Jingle {

    class GLOOX_API IBB : public Plugin  {
        public:

            enum Action {
                init,
                open,
                data
            };

            struct Data {
                int seq;
                std::string chunk;
            };

            /**
             * Constructs a new instance.
             * @param pwd The @c pwd value.
             * @param ufrag The @c ufrag value.
             * @param candidates A list of connection candidates.
             */
            IBB(const std::string &sid, long blockSize);

            /**
             * Constructs a new instance from the given tag.
             * @param tag The Tag to parse.
             */
            IBB(const Tag *tag = 0);

            /**
             * Virtual destructor.
             */
            virtual ~IBB() {}

            const std::string &sid() const { return m_sid; }

            long blockSize() const { return m_blockSize; }

            Action action()const {return m_action;}

            const Data& getData() const {return m_data;}

            // reimplemented from Plugin
            virtual const StringList features() const;

            // reimplemented from Plugin
            virtual const std::string &filterString() const;

            // reimplemented from Plugin
            virtual Tag *tag() const;

            // reimplemented from Plugin
            virtual Plugin *newInstance(const Tag *tag) const;

            // reimplemented from Plugin
            virtual Plugin *clone() const {
                return new IBB(*this);
            }

        private:
            std::string m_sid;
            long m_blockSize;
            Action m_action;
            Data m_data;
        };
    }
}

#endif