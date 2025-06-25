#include "System.h"

int main() {
    System::run();
}

/*
register manager Ivan Ivanov 0880880888 44 Password
register manager III III 0880880888 10 PP

logout
leave

register cashier Gosho Ghoshov 0123456789 31 Parola

login 1 Password
login 2 Parola
login 1 wPassword

sell

list-user-data
list-workers

list-pending

approve 2 SPECIAL
approve 3 SPECIAL
promote-cashier 2 SPECIAL
promote-cashier 3 SPECIAL
decline 4 SPECIAL
fire-cashier 4 SPECIAL

add-category Meat Meat is delicious
delete-category 1

add-product by_unit Steak 1 9.99
add-product by_weight Beef 1 17.99

delete-product 1
delete-product 2

load-products data//products-initializer.txt
load-products data//product-loader.txt

add-product by_weight Cheese 3 16.99

list-products
list-products 1

list-feed
list-transactions
list-categories
*/