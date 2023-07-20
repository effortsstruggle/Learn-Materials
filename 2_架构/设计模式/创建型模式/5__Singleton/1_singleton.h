#ifndef _SINGLETON_H__
#define _SINGLETON_H__

#include <iostream>
#include <memory>
#include <mutex>

/**
  单例模式
**/
#define DECLEAR_SINGLETON(CLASS) \
public: \
    static CLASS* getInstance(); \
    void PrintAddress() const \
    { \
        std::cout << this << std::endl; \
    } \
    virtual ~CLASS() {}; \
protected: \
    CLASS() {}; \
    static std::shared_ptr<CLASS> m_pSington; \
private: \
    CLASS(const CLASS&) = delete; \
    CLASS& operator=(const CLASS&) = delete; \


#define DECLEAR_SINGLETON_STATIC_FUNC(CLASS) \
CLASS* CLASS::getInstance() \
{ \
   static std::once_flag s_flag; \
   std::call_once(s_flag, [&]() { \
   m_pSington.reset(new CLASS()); \
}); \
   return m_pSington.get(); \
}


//静态变量
#define DECLEAR_SINGLETON_STATIC_VARIABLE(CLASS) \
    std::shared_ptr<CLASS> CLASS::m_pSington;
#endif
