//---------------------------------------------------------------------------

#pragma hdrstop

#include "Racer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

String Person::getAge(void)const{
	String astr=(Now()-DoB).FormatString("yy");
	return  astr;
}
TDate Person::getage(void)const{
	return DoB;
}
void Person::setAge(String dob){
	AnsiString adob;
	adob=dob.c_str();

	DoB=StrToDate(adob);
}
void Person::setage(TDate dob){
	DoB=dob;
}


AnsiString Person::getName(int language)const{ return Name[language]+" ";}
AnsiString Person::getI(int language)const{ return Name[language].SubString(1,1).UpperCase()+".";}
AnsiString Person::getO(int language)const{ return SecondName[language].SubString(1,1).UpperCase()+".";}
AnsiString Person::getSecondName(int language)const{ return SecondName[language]+" ";}
AnsiString Person::getSurName(int language)const{ return Surname[language];}
AnsiString Person::getSURNAME(int language)const{ return Surname[language].UpperCase()+" ";}

AnsiString Person::getFIO(int language)const{ return getSURNAME(language)+" "+getName(language)+getSecondName(language);}
AnsiString Person::getIOF(int language)const{ return getName(language)+getSecondName(language)+getSURNAME(language);}
AnsiString Person::getFio(int language)const{ return getSURNAME(language)+" "+getI(language)+getO(language);}
AnsiString Person::getioF(int language)const{ return getI(language)+getO(language)+getSURNAME(language);}

void Person::setName(int language,AnsiString  name){Name[language]=name;}
void Person::setSecondName(int language,AnsiString secondname){SecondName[language]=secondname;}
void Person::setSurName(int language,AnsiString surname){Surname[language]=surname;}


AnsiString Racer::getFIScode(){return FIScode;};
void Racer::setFIScode(AnsiString sfis){FIScode=sfis;};

void Racer::setRacerName(Person *p) {
  setName(0,p->getName(0));
  setName(1,p->getName(1));
};
void Racer::setRacerSecondName(Person *p){
  setSecondName(0,p->getSecondName(0));
  setSecondName(1,p->getSecondName(1));
};
void Racer::setRacerSurName(Person *p){
  setSurName(0,p->getSurName(0));
  setSurName(1,p->getSurName(1));
};

void Racer::setRacerAge(Person *p){
String dob;
AnsiString adob;
	adob=p->getage().FormatString("dd.mm.yyyy");
	dob=adob.c_str();
	setAge(dob);
};

void Racer::setPerson(Person *p){
	setRacerName(p);
	setRacerSecondName(p);
	setRacerSurName(p);
	setRacerAge(p);
}




