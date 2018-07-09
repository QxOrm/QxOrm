#ifndef _QX_BLOG_EXPORT_H_
#define _QX_BLOG_EXPORT_H_

#ifdef _BUILDING_QX_BLOG
#define QX_REGISTER_HPP_QX_BLOG     QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_QX_BLOG     QX_REGISTER_CPP_EXPORT_DLL
#else
#define QX_REGISTER_HPP_QX_BLOG     QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_QX_BLOG     QX_REGISTER_CPP_IMPORT_DLL
#endif // _BUILDING_QX_BLOG

#ifdef Q_OS_WIN
#define QX_BLOG_DLL_EXPORT __declspec(dllexport)
#define QX_BLOG_DLL_IMPORT __declspec(dllimport)
#else
#define QX_BLOG_DLL_EXPORT
#define QX_BLOG_DLL_IMPORT
#endif // Q_OS_WIN

#ifdef Q_OS_WIN
#ifndef _BUILDING_QX_BLOG
#undef QX_BLOG_DLL_EXPORT
#define QX_BLOG_DLL_EXPORT QX_BLOG_DLL_IMPORT
#endif // _BUILDING_QX_BLOG
#endif // Q_OS_WIN

#endif // _QX_BLOG_EXPORT_H_
