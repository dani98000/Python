#ifndef OL69_BT_H
#define OL69_BT_H

#include <stdint.h> /* uint32_t */
#include <stdio.h> /* size_t */

typedef struct bt bt_t;

bt_t *BTCreate(size_t num_bits);

void BTDestroy(bt_t *bt);

int BTInsert(bt_t *bt, uint32_t data);

int BTRemove(bt_t *bt, uint32_t key);

int BTFind(bt_t *bt, uint32_t key);

size_t BTCount(const bt_t *bt);

size_t BTCountFree(const bt_t *bt);

#endif /* OL69_BT_H */
