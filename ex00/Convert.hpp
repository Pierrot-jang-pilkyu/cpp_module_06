#ifndef CONVERT_HPP
# define CONVERT_HPP
# include <iostream>
# include <float.h>
# include <math.h>
# include <ctype.h>
# include <sstream>
# include <stdlib.h>
# include <stdio.h>
# include <climits>

class Convert
{
private:
	std::string	input;
	char			c;
	int				i;
	float			f;
	double			d;
	int				flag;
	Convert(void);

public:
	Convert(std::string _input);
	Convert(const Convert &obj);
	Convert	&operator=(const Convert &obj);
	~Convert(void);

	std::string	getInput(void) const;
	char		getChar(void) const;
	int			getInt(void) const;
	float		getFloat(void) const;
	double		getDouble(void)const;
	int			getFlag(void) const;
	void		setChar(char _c);
	void		setInt(int _i);
	void		setFloat(float _f);
	void		setDouble(double _d);
	void		setFlag(int _flag);

	bool				isAllDigit(std::string str);
	unsigned int		getFirstChar(std::string str);

	void	cast(void);
	void	printFloat(void);
	void	printDouble(void);
	void	print(void);
};

#endif
