int printf();    
int a[10];
int main()
{
	int i;
	int *p;
	p = &a[5];
	for(i = 0; i < 10; i++)
		a[i] = i;
	for(i = 0; i < 10; i++)
		printf("a[%d] is %d\n", i, a[i]);
	
	if(a[9]==9)
		printf("Hak is god\n");
	else
		printf("Hak is not god\n");
	
	if( (*p) == 4)
		printf("Hak is not god\n");
	else
		printf("Hak is still god\n");
	
	return 69;
}
