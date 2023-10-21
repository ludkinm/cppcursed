#pragma once

#include <memory>
#include <type_traits>

namespace mrl {

namespace detail {
template <class T> struct MemberPtrTypes;
template <class M, class T> struct MemberPtrTypes<M T::*> {
    using Class = T;
    using Member = M;
};
} // namespace detail

// Contraband stores a smuggled pointer-to-member.
// Note it is non-const so the template specialisation can assign to it.
// Since you cannot name a private pointer to member, you have to Tag it when
// specialising Smuggle to access it again via Contraband.
template <class Tag, class MemberPtrType> struct Plunder {
    using Class = typename detail::MemberPtrTypes<MemberPtrType>::Class;
    using Member = typename detail::MemberPtrTypes<MemberPtrType>::Member;
    inline static Member Class::*member = nullptr;
    static constexpr Member &access(Class &c) { return c.*member; };
};

// Specialisations of this class 'smuggle out' a pointer-to-member of a given
// class into the type `Contraband<Tag, Pointer-To-Member-Type>`.
// Since access control is not taken into account during class template
// specialisations, this techinique allows one to bypass access control to
// smuggle out the pointer to member.
template <class Tag, auto MemberPtr> struct Smuggle {
    inline static const auto chain = Plunder<Tag, decltype(MemberPtr)>::member =
        MemberPtr;
};

#define LOOT(TYPE, MEMBER, MEMBER_TYPE)                                        \
    struct Loot##TYPE##MEMBER {                                                \
        using X = ::mrl::Plunder<Loot##TYPE##MEMBER, MEMBER_TYPE TYPE::*>;     \
        constexpr auto &operator()(X::Class &c) { return X::access(c); }       \
    };                                                                         \
    template struct mrl::Smuggle<Loot##TYPE##MEMBER, &TYPE::MEMBER>

} // namespace mrl
