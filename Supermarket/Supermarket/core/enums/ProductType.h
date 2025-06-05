class ProductType {
public:
    enum ProductTypeEnum {
        BY_UNIT,
        BY_WEIGHT
    };

private:
    ProductTypeEnum type;

public:
    ProductType(ProductTypeEnum t) : type(t) {}

    ProductTypeEnum get() const { return type; }

    String toString() const {
        switch (type) {
        case BY_UNIT: return "By Unit";
        case BY_WEIGHT: return "By Weight";
        default: throw std::runtime_error("Invalid type!");
        }
    }

    static ProductType get(const String& type) {
        if (type.lowered() == String("by unit")) { return ProductType::BY_UNIT; }
        else if (type.lowered() == String("by weight")) { return ProductType::BY_WEIGHT; }
        else { throw std::invalid_argument("Invalid type!"); }
    }

    bool operator==(const ProductType& other) const {
        return type == other.type;
    }
};