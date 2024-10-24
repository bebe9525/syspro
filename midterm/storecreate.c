#include <stdio.h>
#include "db.dat"

int main(int argc, char* argv[]) {
	struct product rec;
	FILE *fp;
	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}
	fp = fopen (argv[1], "w");
	printf("%-4d %-10s %-9s %-13d %-5d", "id", "name", "category", "date", "stock");
	while (scanf("%d %s %s %d %d", &rec.id, rec.name, rec.category, &rec.date, &rec.stock) == 5)
		fprintf(fp, "%d %s %s %d %d\n", rec.id, rec.name, rec.category, rec.date, rec.stock);
	fclose(fp);
	return 0;
}
