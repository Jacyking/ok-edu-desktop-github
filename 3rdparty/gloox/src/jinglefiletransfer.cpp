/*
  Copyright (c) 2013-2019 by Jakob Schröter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warranty.
*/


#include "jinglefiletransfer.h"

#include "tag.h"
#include "gloox.h"
#include "util.h"

#include <cstdlib>
#include <iostream>

namespace gloox
{

  namespace Jingle
  {

    static const char* typeValues [] = {
      "offer",
      "request",
      "checksum",
      "abort",
      "received"
    };

    FileTransfer::FileTransfer( Type type, const FileList& files )
      : Plugin( PluginFileTransfer ), m_type( type ), m_files( files )
    {
    }

    FileTransfer::FileTransfer( const Tag* tag )
      : Plugin( PluginFileTransfer ), m_type( Invalid )
    {
      if(!tag)
        return;

        /**
           * <iq type='set' id='RQSC71EUrtiU'
           * to='18910221510@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
           * from='18510248810@meet.chuanshaninfo.com/monocles chat[1.5.14].rbUZ'>
           * <jingle action='session-initiate' sid='Dspa++nv6Or4yO6jZY21Cw' xmlns='urn:xmpp:jingle:1'>
           * <content creator='initiator' senders='initiator' name='f6/TB36I+Ohpp/E9xdueYw'>
           *    <description xmlns='urn:xmpp:jingle:apps:file-transfer:5'>
           *        <file><size>3387509</size><name>IMG_20230413_235000.jpg</name></file>
           *    </description>
           *    <transport sid='5/UN/9BKkfviMxjYWgGi7w' block-size='8192' xmlns='urn:xmpp:jingle:transports:ibb:1'/>
           * </content>
           * </jingle></iq>
           *
           * <iq type='set' id='qAPh7dzO3g7n' to='18910221510@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
           * from='13975412395@meet.chuanshaninfo.com/monocles chat[1.5.13].Nz2u'>
           * <jingle sid='0fce057fa94159301724944087134afa79a745d400000050'
           * action='session-accept' xmlns='urn:xmpp:jingle:1'>
           * <content senders='both' creator='initiator' name='offer-a-file'>
           * <description xmlns='urn:xmpp:jingle:apps:file-transfer:3'>
           * <offer><file><date/><name>replay_pid4573.log</name><desc/><size>2695864</size><range offset='-1'/></file></offer>
           * </description>
           * <transport sid='replay_pid4573.log' block-size='4096' xmlns='urn:xmpp:jingle:transports:ibb:1'/></content></jingle></iq>
           *
           */
      std::string name = tag->name();
      if( name == "description" )
      {
          std::string xmlns = tag->xmlns();
          if(xmlns == XMLNS_JINGLE_FILE_TRANSFER){
              //v3
              const Tag* c = tag->findTag( "description/offer|description/request" );
              const TagList f2 = c->findChildren( "file" );
              if( !f2.empty() )
              {
                  parseFileList( f2 );
              }
              m_type = static_cast<Type>( util::lookup( c->name(), typeValues ) );
          }else if(xmlns == XMLNS_JINGLE_FILE_TRANSFER5){
            const TagList f = tag->findChildren( "file" );
            if( !f.empty() )
            {
              parseFileList( f );
            }
          }
      }
      else if( name == "checksum" || name == "abort" || name == "received" )
      {
        parseFileList( tag->findChildren( "file" ) );
        m_type = static_cast<Type>( util::lookup( name, typeValues ) );

      }

    }

    void FileTransfer::parseFileList( const TagList& files )
    {
      TagList::const_iterator it = files.begin();
      for( ; it != files.end(); ++it )
      {
        File f;
        Tag *t = (*it)->findChild( "name" );
        f.name = t ? t->cdata() : EmptyString;
        t = (*it)->findChild( "desc" );
        f.desc = t ? t->cdata() : EmptyString;
        t = (*it)->findChild( "date" );
        f.date = t ? t->cdata() : EmptyString;
        t = (*it)->findChild( "size" );
        f.size = t ? atoi( t->cdata().c_str() ) : -1;
        t = (*it)->findChild( "range" );
        if( t )
        {
          f.range = true;
          f.offset = t->hasAttribute( "offset" ) ? atoi( t->findAttribute( "offset" ).c_str() ) : -1;
        }
        t = (*it)->findChild( "hash", XMLNS, XMLNS_HASHES );
        if( t )
        {
          f.hash_algo = t->findAttribute( "algo" );
          f.hash = t->cdata();
        }
        m_files.push_back( f );
      }
    }

    const StringList FileTransfer::features() const
    {
      StringList sl;
      sl.push_back( XMLNS_JINGLE_FILE_TRANSFER );
      return sl;
    }

    const std::string& FileTransfer::filterString() const
    {
      static const std::string filter = "content/description[@xmlns='" + XMLNS_JINGLE_FILE_TRANSFER + "']"
                                        "|content/description[@xmlns='" + XMLNS_JINGLE_FILE_TRANSFER4 + "']"
                                        "|content/description[@xmlns='" + XMLNS_JINGLE_FILE_TRANSFER5 + "']"
                                        "|jingle/abort[@xmlns='" + XMLNS_JINGLE_FILE_TRANSFER + "']"
                                        "|jingle/received[@xmlns='" + XMLNS_JINGLE_FILE_TRANSFER + "']"
                                        "|jingle/checksum[@xmlns='" + XMLNS_JINGLE_FILE_TRANSFER + "']";
      return filter;
    }

    Plugin* FileTransfer::newInstance( const Tag* tag ) const
    {
      return new FileTransfer( tag );
    }

    Tag* FileTransfer::tag() const
    {
      if( m_type == Invalid )
        return 0;

      Tag* r = 0;

      switch( m_type )
      {
        case Offer:
        case Request:
        {
          r = new Tag( "description", XMLNS, XMLNS_JINGLE_FILE_TRANSFER );
          Tag* o = new Tag( r, util::lookup( m_type, typeValues ) );
          FileList::const_iterator it = m_files.begin();
          for( ; it != m_files.end(); ++it )
          {
            Tag* f = new Tag( o, "file" );
            new Tag( f, "date", (*it).date );
            new Tag( f, "name", (*it).name );
            new Tag( f, "desc", (*it).desc );
            new Tag( f, "size", util::long2string( (*it).size ) );

            if(!(*it).hash.empty()){
                Tag* h = new Tag( f, "hash", XMLNS, XMLNS_HASHES );
                h->addAttribute( "algo", (*it).hash_algo );
                h->setCData( (*it).hash );
            }

            if( (*it).range )
              new Tag( f, "range", "offset", (*it).offset ? util::long2string( (*it).offset ) : EmptyString );
          }
          break;
        }
        case Abort:
        case Checksum:
        case Received:
        {
          r = new Tag( util::lookup( m_type, typeValues ), XMLNS, XMLNS_JINGLE_FILE_TRANSFER );
          FileList::const_iterator it = m_files.begin();
          Tag* f = new Tag( r, "file" );
          new Tag( f, "date", (*it).date );
          new Tag( f, "name", (*it).name );
          new Tag( f, "desc", (*it).desc );
          new Tag( f, "size", util::long2string( (*it).size ) );
          Tag* h = new Tag( f, "hash", XMLNS, XMLNS_HASHES );
          h->addAttribute( "algo", (*it).hash_algo );
          h->setCData( (*it).hash );
          if( (*it).range )
            new Tag( f, "range" );
          break;
        }
        default:
          break;
      }

      return r;
    }

  }

}
