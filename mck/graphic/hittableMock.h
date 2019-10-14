#pragma once

#include "graphic/hittable.h"

#include <gmock/gmock.h>

namespace graphic {
bool operator==(const hit_record& lhs, const hit_record& rhs);
bool operator==(const ray& lhs, const ray& rhs);
namespace mck {
class hittable_mock : public hittable {
public:
    hittable_mock();
    ~hittable_mock() noexcept override;

    MOCK_CONST_METHOD4(hit, bool(const ray&, float, float, hit_record&));
};
}
}
