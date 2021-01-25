#ifndef GENHIERARCHIES_H
#define GENHIERARCHIES_H

#include "Typelist.h"

namespace CasaEngine
{
	////////////////////////////////////////////////////////////
	/// Hiérarchie "éparpillée"
	////////////////////////////////////////////////////////////
	template <class TList, template <class> class Handler> class CScatteredHierarchy;

	template
		<
		class T1,
		class T2,
		template <class> class Handler
		>
		class CScatteredHierarchy<TypeList<T1, T2>, Handler> : public Handler<T1>, public CScatteredHierarchy<T2, Handler>
	{
	};

	template
		<
		class T,
		template <class> class Handler
		>
		class CScatteredHierarchy<TypeList<T, NullType>, Handler> : public Handler<T>
	{
	};

	template
		<
		template <class> class Handler
		>
		class CScatteredHierarchy<NullType, Handler>
	{
	};

	////////////////////////////////////////////////////////////
	/// Hiérarchie "linéaire"
	////////////////////////////////////////////////////////////
	template <class TList, template <class, class> class Handler, class Root = NullType> class CLinearHierarchy;

	template
		<
		class T1,
		class T2,
		template <class, class> class Handler,
		class Root
		>
		class CLinearHierarchy<TypeList<T1, T2>, Handler, Root> : public Handler<T1, CLinearHierarchy<T2, Handler, Root> >
	{
	};

	template
		<
		class T,
		template <class, class> class Handler,
		class Root
		>
		class CLinearHierarchy<TypeList<T, NullType>, Handler, Root> : public Handler<T, Root>
	{
	};
}

#endif // GENHIERARCHIES_H
