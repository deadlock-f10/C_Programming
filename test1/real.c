#include <stdio.h>
#include <stdbool.h>
#define string_len  30
char string[string_len];
char *ptr = string;
enum {
	format1=1,format2
};
int  format = format1;
bool check_Integer();
bool check_OptFraction();
bool check_OptExponent();
bool check_OptSign();         //always true
bool check_digit();
bool check_nz_digit();
bool check_digits();         //always true
int main(){
	FILE *in,*out;
	in = fopen("real.in","r");
	out = fopen("real.out","w");
//	fscanf(in,"%s",string);
	fgets(string , string_len , in);
	if(check_Integer() && check_OptFraction() && check_OptExponent() && *ptr=='\n')
		fprintf(out,"Format%d\n",format);
	else
		fprintf(out,"Wrong\n");
	fclose(in);
	fclose(out);
	return 0;
}
bool check_Integer(){
	bool Bool = true;
	Bool &= check_OptSign();
	if(*ptr == '0'){
		ptr++;
		Bool &= true;
	}
	else if(check_nz_digit()){
		Bool &= true;
		Bool &= check_digits();
	}
	else
		Bool = false;
	return Bool;
}
bool check_nz_digit(){
	if(('1' <= *ptr) && (*ptr <= '9'))
	{
		ptr++;
		return true;
	}
	else
		return false;
}
bool check_digit(){
	if(check_nz_digit())
		return true;
	else if(*ptr == '0'){
		ptr++;
		return true;
	}
	else
		return false;
}
bool check_digits(){
	while(check_digit())
		;
	return true;
}
bool check_OptSign(){
	if(*ptr == '+' || *ptr == '-')
	{
		ptr++;
		return true;
	}
	else
		return true;
}
bool check_OptFraction(){
	if(*ptr == '.')
	{
		ptr++;
		if(check_digit() && check_digits())
			return true;
		else
			return false;
	}
	else 
		return true;
}
bool check_OptExponent(){
	if(*ptr == 'E')
	{
		ptr++;
		if(check_Integer())
		{
			format = format2;
			return true;
		}
		else
			return false;
	}
	else 
		return true;
}
