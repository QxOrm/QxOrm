#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#if _QX_SERIALIZE_PORTABLE_BINARY
#ifndef _QX_PORTABLE_ARCHIVE_EXCEPTION_H_
#define _QX_PORTABLE_ARCHIVE_EXCEPTION_H_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <boost/lexical_cast.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/archive_exception.hpp>

namespace eos {

   // this value is written to the top of the stream
   const signed char magic_byte = 'e' | 'o' | 's';

   // version of the linked boost archive library
   const boost::archive::version_type archive_version(
      #if BOOST_VERSION < 103700
         boost::archive::ARCHIVE_VERSION()
      #else
         boost::archive::BOOST_ARCHIVE_VERSION()
      #endif
	);

   /**
   * \brief Exception being thrown when serialization cannot proceed.
   *
   * There are several situations in which the portable archives must fail and
   * hence throw an exception: 
   * -# deserialization of an integer value that exceeds the range of the type 
   * -# serialization of special floating point values nan or inf 
   * -# deserialization of a denormalized value without the floating point type
   *    supporting denormalized numbers
   *
   * Note that this exception will also be thrown if you mixed up your stream
   * position and accidentially interpret some value for size data (in this case
   * invalid_size will be totally amiss most of the time).
   */
   class portable_archive_exception : public boost::archive::archive_exception
   {
      std::string msg;

      public:

      //! type size is not large enough for deserialized number
      portable_archive_exception(signed char invalid_size) : boost::archive::archive_exception(other_exception), msg("requested integer size exceeds type size: ")
      {
         msg += boost::lexical_cast<std::string, int>(invalid_size);
      }

      //! negative number in unsigned type
      portable_archive_exception() : boost::archive::archive_exception(other_exception), msg("cannot read a negative number into an unsigned type") { ; }

      //! serialization of inf, nan and denormals
      template <typename T> 
      portable_archive_exception(const T& abnormal) : boost::archive::archive_exception(other_exception), msg("serialization of non-portable floating point value: ")
      {
         msg += boost::lexical_cast<std::string>(abnormal);
      }

      //! override the base class function with our message
      const char* what() const throw() { return msg.c_str(); }
      ~portable_archive_exception() throw() { ; }
   };

} // namespace eos

#endif // _QX_PORTABLE_ARCHIVE_EXCEPTION_H_
#endif // _QX_SERIALIZE_PORTABLE_BINARY
#endif // _QX_ENABLE_BOOST_SERIALIZATION
