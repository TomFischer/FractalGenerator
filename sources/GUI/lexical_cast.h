#ifndef _LEXICAL_CAST_H
#define _LEXICAL_CAST_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

// von http://www.zfx.info/Display/Thread.php?TID=177779

#include <string>
#include <sstream>

#ifdef UNICODE
typedef std::wstringstream unistringstream;
typedef std::wstring unistring;
#else
typedef std::stringstream unistringstream;
typedef std::string unistring;
#endif

template < typename A, typename T > inline const A lexical_cast (const T& source)
{
   unistringstream s;

   s << source;

   A destination;
   s >> destination;

   return (destination);
}

#endif /* _LEXICAL_CAST_H */

/* Anwendungsbeispiel

unistring pi_as_unistring = lexical_cast < unistring > (3.14f);
float pi_as_float = lexical_cast < float > (pi_as_unistring.c_str ());
*/
