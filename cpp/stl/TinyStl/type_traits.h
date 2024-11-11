#ifndef MYSTL_TYPE_TRAITS_H_
#define MYSTL_TYPE_TRAITRS_H_

#include<type_traits>
namespace mystl{

//���������ṹ�壬�ɽ���ͬ��������ϳ�һ��������
template<class T,T v>
struct m_integral_constant
{
    static constexpr T value=v;//constexprָ��һ������ʽ�����ڱ���ʱ�Ϳ�����ֵ�õ��������   
};

template<bool b>
using m_bool_constant=m_integral_constant<bool,b>; //m_bool_constantΪһ������
typedef m_bool_constant<true>  m_true_type;
typedef m_bool_constant<false> m_false_type;


template <class T1,class T2>
struct pair;
template<class T>
struct is_pair:mystl::m_false_type{};//is_pair�̳���mystl::my_false_type

template<class T1,class T2>
struct is_pair<mystl::pair<T1,T2>>:mystl::m_true_type{};
}

#endif