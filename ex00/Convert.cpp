#include "Convert.hpp"

Convert::Convert(void) : input(""), c('\0'), i(0), f(0.0f), d(0.0), flag(0) {}

Convert::Convert(std::string _input) : c('\0'), i(0), f(0.0f), d(0.0), flag(0)
{
	try
	{
		this->input = _input;
	}
	catch(const std::bad_alloc &e)
	{
		flag = 4;
	}
	
}

Convert::Convert(const Convert &obj) : input(obj.getInput())
{
	this->c = obj.getChar();
	this->i = obj.getInt();
	this->f = obj.getFloat();
	this->d = obj.getDouble();
	this->flag = obj.getFlag();
}

Convert &Convert::operator=(const Convert &obj)
{
	// standard
	(void)obj;
	std::cout << "Wrong using operator. Because of having const member attribute.\n";
	return (*this);

	/* A case of using const_cast

	std::string* temp = const_cast<std::string*>(&this->name);
	*temp = obj.getName();
	this->c = obj.getChar();
	this->i = obj.getInt();
	this->f = obj.getFloat();
	this->d = obj.getDouble();
	this->flag = obj.getFlag();
	return (*this);

	*/
}


Convert::~Convert(void) {}

std::string Convert::getInput(void) const
{
	return (this->input);
}

char Convert::getChar(void) const
{
	return (this->c);
}

int Convert::getInt(void) const
{
	return (this->i);
}

float Convert::getFloat(void) const
{
	return (this->f);
}

double Convert::getDouble(void) const
{
	return (this->d);
}

int Convert::getFlag(void) const
{
	return (this->flag);
}

void Convert::setChar(char _c)
{
	this->c = _c;
}

void Convert::setInt(int _i)
{
	this->i = _i;
}

void Convert::setFloat(float _f)
{
	this->f = _f;
}

void Convert::setDouble(double _d)
{
	this->d = _d;
}

void Convert::setFlag(int _flag)
{
	this->flag = _flag;
}

bool	Convert::isAllDigit(std::string str)
{
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (!std::isdigit(str[i]))
			return (false);
	}
	return (true);
}

unsigned int	Convert::getFirstChar(std::string str)
{
	unsigned int res = 0;

	for (; res < str.length(); ++res)
	{
		if (!std::isdigit(str[res]))
			return (res);
	}
	return (-1);
}

void Convert::cast(void)
{
	if (flag == 4)
		return ;
	std::string s = this->input;

	std::string::size_type dot = s.find('.');

	if (s == "nan" || s == "inf" || s == "+inf" || s == "-inf" || \
		s == "nanf" || s == "inff" || s == "+inff" || s == "-inff")
	{
		if (s == "nan" || s == "nanf")
		{
			flag = 2;
			this->d = sqrt(-1.0);
		}
		else
		{
			flag = 2;
			if (s[0] == '-')
			{
				this->d = DBL_MAX * -10;
				this->f = static_cast<float>(this->d);
			}
			else
			{
				this->d = DBL_MAX * 10;
				this->f = static_cast<float>(this->d);
			}
		}
		this->f = static_cast<float>(d);
	}
	else if (s.length() == 1 && !std::isdigit(static_cast<char>(s[0])))
	{
		this->c = static_cast<char>(s[0]);
		this->i = static_cast<int>(this->c);
		this->f = static_cast<float>(this->i);
		this->d = static_cast<double>(this->i);
	}
	else if (dot == std::string::npos)
	{
		if (s.length() > 309)
		{
			this->flag = 4;
			return ;
		}
		std::stringstream ss;
		ss << s;
		double _d;
		while (ss >> _d) this->d = _d;
		if (!isAllDigit(s))
		{
			unsigned int end = getFirstChar(s);
			if (s[end] == 'f' && end == s.length() - 1)
			{
				if (this->d > 255 || this->d < 0)
					flag = 1;
				else
					this->c = static_cast<char>(this->d);
				if (this->d > static_cast<double>(INT_MAX) || this->d < static_cast<double>(INT_MIN))
					flag = 2;
				else
					this->i = static_cast<int>(this->d);
				
				this->f = static_cast<float>(this->d);
			}
			else
				flag = 4;
		}
		else
		{
			if (this->d > 255 || this->d < 0)
				flag = 1;
			else
				this->c = static_cast<char>(this->d);
			if (this->d > static_cast<double>(INT_MAX) || this->d < static_cast<double>(INT_MIN))
				flag = 2;
			else
				this->i = static_cast<int>(this->d);
			
			this->f = static_cast<float>(this->d);
		}
	}
	else
	{
		char *end = NULL;

		this->d = strtod(s.c_str(), &end);

		if (*end && !(*end == 'f' && end == &s.c_str()[s.length() - 1]))
			flag = 4;
		else
		{
			if (this->d > 255 || this->d < 0)
				flag = 1;
			else
				this->c = static_cast<char>(this->d);
			if (this->d > static_cast<double>(INT_MAX) || this->d < static_cast<double>(INT_MIN))
				flag = 2;
			else
				this->i = static_cast<int>(this->d);
			
			this->f = static_cast<float>(this->d);
		}
	}
}

void	Convert::printFloat(void)
{
	int digit = 0;
	float temp = this->f;

	while (temp > 1)
	{
		temp = temp / 10;
		digit++;
	}
	if (digit >= 9)
		std::cout << "float: " << this->f << "f" << std::endl;
	else
	{
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "float: " << this->f << "f" << std::endl;
	}
}

void	Convert::printDouble(void)
{
	int digit = 0;
	double temp = this->d;

	while (temp > 1)
	{
		temp = temp / 10;
		digit++;
	}
	if (digit >= 17)
		std::cout << "double: " << this->d << std::endl;
	else
	{
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "double: " << this->d << std::endl;
	}
}

void	Convert::print(void)
{
	std::string err_msg = "impossible";

	switch (this->flag)
	{
	case 1:
		std::cout << "char: " << err_msg <<std::endl;
		std::cout << "int: " << this->i << std::endl;
		printFloat();
		printDouble();
		break;

	case 2:
		std::cout << "char: " << err_msg <<std::endl;
		std::cout << "int: " << err_msg << std::endl;
		printFloat();
		printDouble();
		break;

	case 4:
		std::cout << "char: " << err_msg <<std::endl;
		std::cout << "int: " << err_msg << std::endl;
		std::cout << "float: " << err_msg << std::endl;
		std::cout << "double: " << err_msg << std::endl;
		break;
	
	default:
		if (std::isprint(this->c))
			std::cout << "char: " << this->c <<std::endl;
		else
			std::cout << "char: " << "Non displayable" <<std::endl;
		std::cout << "int: " << this->i << std::endl;
		printFloat();
		printDouble();
		break;
	}
}
