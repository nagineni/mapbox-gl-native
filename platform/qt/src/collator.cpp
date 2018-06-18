#include <mbgl/style/expression/collator.hpp>
#include <mbgl/util/platform.hpp>

namespace mbgl {
namespace style {
namespace expression {

class Collator::Impl {
public:
    Impl(bool caseSensitive_, bool diacriticSensitive_, optional<std::string>)
        : caseSensitive(caseSensitive_)
        , diacriticSensitive(diacriticSensitive_)
    {}

    bool operator==(const Impl& other) const {
        return caseSensitive == other.caseSensitive &&
            diacriticSensitive == other.diacriticSensitive;
    }

    int compare(const std::string& lhs, const std::string& rhs) const {
        //TODO: Use QCollator once QTBUG-22727 is fixed
        return lhs.compare(rhs);
    }

    std::string resolvedLocale() const {
        return "";
    }
private:
    bool caseSensitive;
    bool diacriticSensitive;
};


Collator::Collator(bool caseSensitive, bool diacriticSensitive, optional<std::string> locale_)
    : impl(std::make_shared<Impl>(caseSensitive, diacriticSensitive, std::move(locale_)))
{}

bool Collator::operator==(const Collator& other) const {
    return *impl == *(other.impl);
}

int Collator::compare(const std::string& lhs, const std::string& rhs) const {
    return impl->compare(lhs, rhs);
}

std::string Collator::resolvedLocale() const {
    return impl->resolvedLocale();
}


} // namespace expression
} // namespace style
} // namespace mbgl
