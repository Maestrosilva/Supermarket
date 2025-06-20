#pragma once
#include "..//..//..//utils//_Utils.h"
#include "../..//enums//IdType.h"
#include "Product.h"
#include <fstream>

struct Pair {
    String productId;
    double quantity;
};

class Transaction : public Serializable {
private:
    String id;
    String cashierId;
    String date;
    Vector<Pair> pairs;

    bool ended = false;
    double total = 0;

public:
    static const String FILE_NAME;

    Transaction() = default;
    Transaction(const String& cashierId);

    void add(const Product* product, double quantity);

    const String& getId() const;
    const String& getCashierId() const;
    const String& getDate() const;
    const Vector<Pair>& getPairs() const;
    double totalPrice() const;

    String toString() const;

    void endTransaction();

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

    ~Transaction() = default;
};