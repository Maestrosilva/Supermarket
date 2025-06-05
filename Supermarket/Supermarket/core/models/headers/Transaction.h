#pragma once
#include "..//..//..//utils//_Utils.h"
#include "../..//enums//IdType.h"
#include "..//..//System.h"
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
    String receipt = "";


public:
    static const String FILE_NAME;

    Transaction() = default;
    Transaction(const String& cashierId);

    void add(const Pair& pair);

    const String& getId() const;
    const String& getCashierId() const;
    double totalPrice() const;

    String toString() const;

    void endTransaction();

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

    ~Transaction() = default;
};