#pragma once
#include <functional>
#include <list>

template<typename T>
class ObservableValue
{
public:
    explicit ObservableValue(const T& initialValue = T());

    void setValue(const T& value);
    const T& value() const;

    void onChanged(const std::function<void(const T&)>& cb);

private:
    T currentValue_;
    std::list<std::function<void(const T&)>> onChangedObservers_;
};

template<typename T>
ObservableValue<T>::ObservableValue(const T& initialValue)
    : currentValue_(initialValue)
{
}

template<typename T>
void ObservableValue<T>::setValue(const T& value)
{
    if (value != currentValue_) {
        currentValue_ = value;
        for(const auto cb : onChangedObservers_) {
            cb(currentValue_);
        }
    }
}

template<typename T>
const T& ObservableValue<T>::value() const
{
    return currentValue_;
}

template<typename T>
void ObservableValue<T>::onChanged(const std::function<void(const T&)>& cb)
{
    onChangedObservers_.push_back(cb);
}
