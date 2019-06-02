typedef struct CBUF cbuf_t;
/* struct CBUF
{
    size_t capacity;
    size_t size;
    size_t read_offset;
    void *buff;
}*/
cbuf_t *CBUFCreate(size_t nbytes);
void CBUFDestroy(cbuf_t *cbuf);
size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes);
size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes);
int CBUFIsEmpty(const cbuf_t *cbuf);
size_t CBufFreeSpace(cbuf_t *cbuf);
size_t CBufCapacity(cbuf_t *cbuf);
