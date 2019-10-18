uint16_t satsum(uint16_t x, uint16_t y) {
    uint16_t sum = x + y;
    return sum < x ? ~0 : sum;
}
