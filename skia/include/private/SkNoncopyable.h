//
// Created by wangrl on 19-4-17.
//

#pragma once

/**
 * SkNoncopyable is the base class for objects that do not want to
 * be copied. It hides its copy-constructor and its assignment-operator.
 */
class SkNoncopyable {
public:
    SkNoncopyable() = default;

    SkNoncopyable(SkNoncopyable&&) = default;
    SkNoncopyable& operator =(SkNoncopyable&&) = default;

private:
    SkNoncopyable(const SkNoncopyable&) = delete;
    SkNoncopyable&operator=(const SkNoncopyable&) = delete;
};
