
#ifndef TYPELIST_H
#define TYPELIST_H


namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Structure d'une typelist (liste de types)
    ////////////////////////////////////////////////////////////
    template <class T1, class T2>
    struct TypeList
    {
        typedef T1 Head;
        typedef T2 Tail;
    };

    ////////////////////////////////////////////////////////////
    /// Marqueur de fin de liste
    ////////////////////////////////////////////////////////////
    struct NullType {};

    ////////////////////////////////////////////////////////////
    // Macros servant à construire des typelists
    ////////////////////////////////////////////////////////////
    #define TYPELIST_1(t1)                                 CasaEngine::TypeList<t1, CasaEngine::NullType>
    #define TYPELIST_2(t1, t2)                             CasaEngine::TypeList<t1, TYPELIST_1(t2) >
    #define TYPELIST_3(t1, t2, t3)                         CasaEngine::TypeList<t1, TYPELIST_2(t2, t3) >
    #define TYPELIST_4(t1, t2, t3, t4)                     CasaEngine::TypeList<t1, TYPELIST_3(t2, t3, t4) >
    #define TYPELIST_5(t1, t2, t3, t4, t5)                 CasaEngine::TypeList<t1, TYPELIST_4(t2, t3, t4, t5) >
    #define TYPELIST_6(t1, t2, t3, t4, t5, t6)             CasaEngine::TypeList<t1, TYPELIST_5(t2, t3, t4, t5, t6) >
    #define TYPELIST_7(t1, t2, t3, t4, t5, t6, t7)         CasaEngine::TypeList<t1, TYPELIST_6(t2, t3, t4, t5, t6, t7) >
    #define TYPELIST_8(t1, t2, t3, t4, t5, t6, t7, t8)     CasaEngine::TypeList<t1, TYPELIST_7(t2, t3, t4, t5, t6, t7, t8) >
    #define TYPELIST_9(t1, t2, t3, t4, t5, t6, t7, t8, t9) CasaEngine::TypeList<t1, TYPELIST_8(t2, t3, t4, t5, t6, t7, t8, t9) >


    ////////////////////////////////////////////////////////////
    // Quelques opérations utiles sur les typelists
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// Recherche le N-ième élément d'une typelist
    ////////////////////////////////////////////////////////////
    template <std::size_t N, class List> struct NthElement;

    ////////////////////////////////////////////////////////////
    /// Détermine de la taille d'une typelist
    ////////////////////////////////////////////////////////////
    template <class List> struct Size;

    ////////////////////////////////////////////////////////////
    /// Recherche la position d'un élément dans une typelist
    ////////////////////////////////////////////////////////////
    template <class ToFind, class List> struct Find;

    ////////////////////////////////////////////////////////////
    /// Ajoute un élément à la fin d'une typelist
    ////////////////////////////////////////////////////////////
    template <class T, class List> struct PushBack;

    ////////////////////////////////////////////////////////////
    /// Ajoute d'un élément au début d'une typelist
    ////////////////////////////////////////////////////////////
    template <class T, class List> struct PushFront;

    ////////////////////////////////////////////////////////////
    /// Concatène 2 typelists
    ////////////////////////////////////////////////////////////
    template <class List1, class List2> struct Concat;

    #include "Typelist.inl"

} // namespace CasaEngine


#endif // TYPELIST_H
