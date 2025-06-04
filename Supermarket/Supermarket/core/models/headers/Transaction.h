#pragma once
#include "..//..//..//utils//_Utils.h.h"
#include "Cashier.h"
#include <fstream>

struct Pair {
    String productId;
    double quantity;
};

class Transaction : public Serializable {
private:
    const String id;
    const String cashierId;
    String date;
    Vector<Pair> pairs;

    bool ended = false;

    static constexpr const String FILE_NAME = "..//..//receipts//receipt_";

public:
    Transaction(const String& cashierId);

    void add(const Pair& pair);

    String toString() const;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

    ~Transaction();
};