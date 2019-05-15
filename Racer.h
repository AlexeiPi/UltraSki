//---------------------------------------------------------------------------
#ifndef RacerH
#define RacerH
#include <vcl.h>
enum NameLanguage{rus=0,lat};
class Person {
	private:
		AnsiString Name[2],SecondName[2],Surname[2];
		TDate DoB;
	public:
		Person(){};
		Person(AnsiString name="",AnsiString secondname="",AnsiString surname="",
		  AnsiString  _name="",AnsiString  _secondname="",AnsiString  _surname="",
		  AnsiString dob=""){
			Name[rus]=name;
			SecondName[rus]=secondname;
			Surname[rus]=surname;
			Name[lat]=_name;
			SecondName[lat]=_secondname;
			Surname[lat]=_surname;
			 if(dob.Length()>0)
				DoB=StrToDate(dob);
			 else
				DoB=NULL;
		}
		~Person(){};

		String getAge(void) const;
		void setAge(String);
		void setage(TDate);
		TDate getage(void)const;

//		void setAge(TDate dob);


		AnsiString getName(int language) const ;
		AnsiString getI(int language) const ;
		AnsiString getSecondName(int language) const ;
		AnsiString getO(int language) const;
		AnsiString getSurName(int language) const;
		AnsiString getSURNAME(int language) const;
		AnsiString getFIO(int language) const;
		AnsiString getIOF(int language) const;
		AnsiString getFio(int language) const;
		AnsiString getioF(int language) const;

		void setName(int language,AnsiString  name);
		void setSecondName(int language,AnsiString secondname);
		void setSurName(int language,AnsiString surname);


 };
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 class Racer:public Person {
	private:
		AnsiString FIScode;
	public:
		~Racer(){};
		Racer(AnsiString fiscode="",AnsiString name="",AnsiString secondname="",AnsiString surname="",
		  AnsiString  _name="",AnsiString  _secondname="",AnsiString  _surname="",
		  AnsiString dob=""):
		  Person(name,secondname,surname,_name,_secondname,_surname,dob),FIScode(fiscode){};
		AnsiString getFIScode();
		void setFIScode(AnsiString sfis);
		void setPerson(Person *p);

		void setRacerName(Person *p);
		void setRacerSecondName(Person *p);
		void setRacerSurName(Person *p);
		void setRacerAge(Person *p);

};
//---------------------------------------------------------------------------
#endif
