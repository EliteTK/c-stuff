int main(void)
{
	int i = ({ static int i = 3; i + 5; });
	return i;
}
