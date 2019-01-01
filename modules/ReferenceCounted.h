/*
 Copyright (C) 2018 Erik Ogenvik

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef CYPHESIS_REFERENCECOUNTED_H
#define CYPHESIS_REFERENCECOUNTED_H

#include <cassert>

/**
 * Base class for instances that are reference counted.
 */
class ReferenceCounted
{
    private:
        /// Count of references held by other objects to this instance.
        int m_refCount = 0;

    public:

        virtual ~ReferenceCounted() = default;

        void incRef()
        {
            ++m_refCount;
        }

        /// \brief Decrement the reference count on this instance
        void decRef()
        {
            assert(m_refCount > 0);
            if (--m_refCount == 0) {
                delete this;
            }
        }

        /// \brief Check the reference count on this instance
        int checkRef() const
        {
            return m_refCount;
        }
};

#endif //CYPHESIS_REFERENCECOUNTED_H
