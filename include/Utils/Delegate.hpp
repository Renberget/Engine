#pragma once
#include <forward_list>
#include <functional>

/*!
 * @brief A list of callbacks
 * @tparam Args Callback argument types
 */
template<typename... Args>
class Delegate
{
public:
    using Func = std::function<void(Args...)>;

    Delegate() = default;
    //Constructs delegate with function as first callback
    explicit Delegate(Func&& function)
    {
        mFunctions.push_front(std::move(function));
    }
    //Remove every callback
    void clear()
    {
        mFunctions.clear();
    }
    //Returns true if there is one or more callback
    operator bool() const
    {
        return !mFunctions.empty();
    }
    //Remove all callbacks and add function
    Delegate& operator=(Func&& function)
    {
        mFunctions.clear();
        mFunctions.push_front(std::move(function));
        return *this;
    }
    //Add function to callbacks
    Delegate& operator+=(Func&& function)
    {
        mFunctions.push_front(std::move(function));
        return *this;
    }
    //Remove function from callbacks
    Delegate& operator-=(Func&& function)
    {
        for (auto it = mFunctions.before_begin(); it != mFunctions.end(); ++it)
        {
            if (std::next(it) == function)
            {
                mFunctions.erase_after(it);
            }
        }
        return *this;
    }
    //Invoke callbacks
    void operator()(Args... args) const
    {
        for (auto it = mFunctions.begin(); it != mFunctions.end(); ++it)
        {
            (*it)(std::forward<Args>(args)...);
        }
    }

private:
    std::forward_list<Func> mFunctions;
};
