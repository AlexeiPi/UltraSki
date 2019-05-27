//---------------------------------------------------------------------------
#ifndef RacerH
#define RacerH
#include <vcl.h>
enum NameLanguage{rus=0,lat};
class Person {
	private:
		std::string Fiscode;
		std::string Nation;
		std::string Clubname;

		AnsiString Name[2],SecondName[2],Surname[2];
		TDate DoB;
        int YoB;
		int iGender;
	public:
		Person(){};
		Person(AnsiString name="",AnsiString secondname="",AnsiString surname="",
		  AnsiString  _name="",AnsiString  _secondname="",AnsiString  _surname="",
		  AnsiString gender="",AnsiString dob=""){
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
			if (gender=="M" or gender=="Ì") {
				iGender=1;
			}
			else
				iGender=0;
		}
		~Person(){};

		void setDoB(String);
		void setdob(TDate);
		TDate getdob(void)const;
		String getDoB(void)const;
		String getAge(void) const;
		void setyob(int yob);
		String getYoB(void)  const;
		int getyob(void) const;
		int getYage(void) const;

		String getGender(int language=0) const {
			return language?iGender?"M":"W":iGender?"Ì":"Æ";
		};

		void setGender(String gender){
			iGender=0;
			if (gender=="M" or gender=="Ì") iGender=1;
		}


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
		void setRacerdob(Person *p);
};
//---------------------------------------------------------------------------
#endif
