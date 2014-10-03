****
Baka
****

Exception Library
=================

Macro ``BAKA_EXCEPTION(E, B)``
------------------------------

Defines an exception type named ``E`` that derives from ``B``, and has
an explicit constructor that forwards all arguments to the constructor
of ``B``.

Example::

   #include <baka/exception.hpp>
   #include <stdexcept>

   BAKA_EXCEPTION(precondition_violation, std::logic_error);

   void require(bool condition) {
       if (!condition) {
           throw precondition_violation("precondition violated");
       }
   }

Variadic Utility Library
========================

Metafunction ``NthType<std::size_t N, typename... Ts>``
--------------------------------------------------------

Alias for the ``N``\ th type in ``Ts``.

Example::

   #include <baka/variadic.hpp>

   using my_int = baka::NthType<2, float, double, int>;

Metafunction ``contains_value<typename T, T Needle, T... Haystack>``
--------------------------------------------------------------------

Integral constant that is ``true`` if ``Needle`` is present in
``Haystack``, ``false`` otherwise. ``operator==`` is used for
determining presence.

Example::

   #include <cassert>
   #include <baka/variadic.hpp>

   int main() {
       assert((baka::contains_value<int, 1, 0, 1, 2>));
       assert((!baka::contains_value<int, 3, 0, 1, 2>));
       return 0;
   }

Bound Function Library
======================

Class Template ``bound_function<typename Sig>``
-----------------------------------------------

Allows using a functor where a function pointer is expected.

.. todo:: document this

Dependencies
~~~~~~~~~~~~

``bound_function`` depends on libffi_.

I/O Library
===========

.. todo:: document stream concepts

Exception ``io_error : std::system_error``
------------------------------------------

Exception thrown when an I/O operation fails.

Class ``unique_fd``
-------------------

Owns a file descriptor.

.. todo:: document in detail

Class ``null_stream``
---------------------

``null_stream``\ s meets the requirements of ``ReadableStream`` and
``WritableStream``.

Enum Class ``operation``
------------------------

.. todo:: document

Class Template ``file_stream<typename FD, operation... supported_operations>``
------------------------------------------------------------------------------

.. todo:: document ``FD``

If ``supported_operations`` contains ``operation::read``, ``file_stream`` meets the requirements of ``ReadableStream``.

If ``supported_operations`` contains ``operation::write``, ``file_stream`` meets the requirements of ``WritableStream``.

If ``supported_operations`` contains ``operation::seek``, ``file_stream`` meets the requirements of ``SeekableStream``.

.. todo:: document constructor

.. _libffi: https://sourceware.org/libffi/
