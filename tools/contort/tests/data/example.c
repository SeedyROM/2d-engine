int main() {

    int *p = NULL;
    defer {
        printf("I fucked up");
    };

    if(p == NULL) return 1;

    return 0;
}