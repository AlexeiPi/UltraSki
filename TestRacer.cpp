#include <System.hpp>
#pragma hdrstop

#include <TestFramework.hpp>

#include "Racer.h"
Racer *r1;
Person p1("Иван", "Иванович", "Иванов", "Ivan", "Ivanovich", "Ivanov","08.10.1957");
char ustr[100];

class TTestPerson : public TTestCase {
public:
	__fastcall virtual TTestPerson(System::String name) : TTestCase(name) {
	}
	virtual void __fastcall SetUp();
	virtual void __fastcall TearDown();

__published:
	void __fastcall TestgetAge();
	void __fastcall TestsetAge1();
	void __fastcall Testgetage1();
	void __fastcall TestsetAge2();
	void __fastcall TestgetName();
	void __fastcall TestgetI();
	void __fastcall TestgetSecondName();
	void __fastcall TestgetO();
	void __fastcall TestgetSurName();
	void __fastcall TestgetSURNAME();
	void __fastcall TestgetFIO();
	void __fastcall TestgetIOF();
	void __fastcall TestgetFio();
	void __fastcall TestgetioF();
	void __fastcall TestsetName();
	void __fastcall TestsetSecondName();
	void __fastcall TestsetSurName();
};

class TTestRacer : public TTestCase {
public:
	__fastcall virtual TTestRacer(System::String name) : TTestCase(name) {
	}
	virtual void __fastcall SetUp();
	virtual void __fastcall TearDown();

__published:
	void __fastcall TestgetFIScode();
	void __fastcall TestsetFIScode();
	void __fastcall TestsetPerson();
	void __fastcall TestsetRacerName();
	void __fastcall TestsetRacerSecondName();
	void __fastcall TestsetRacerSurName();
	void __fastcall TestsetRacerAge();
};

void __fastcall TTestPerson::SetUp() {
}

void __fastcall TTestPerson::TearDown() {
}

void __fastcall TTestPerson::TestgetAge() {
	// std::string Person::getAge(void)const

	String dob("08.07.2008"),needed("10");
	r1->setAge(dob);
	dob = r1->getAge();

	int i = dob.Compare(needed);
	sprintf(ustr,"Требуется -> %s - получено -> %s", needed.c_str(), dob.c_str());
	String uob=ustr;
	Check(i==0,uob);
}

void __fastcall TTestPerson::TestsetAge1() {
	// AnsiString setAge(void)
	String str;
	TDate dobset("08.07.2008"),dobget;
	str=dobset.FormatString("dd.mm.yyyy");
	r1->setAge(str);
	dobget = r1->getage();
	sprintf(ustr,"Требуется -> %s - получено -> %s",dobset.FormatString("yyyy.mm.dd"), dobget.FormatString("yyyy.mm.dd"));
	String uob=ustr;
	Check(dobget==dobset,uob);
}

void __fastcall TTestPerson::Testgetage1() {
	// TDate getage(void)
	TDate dobget,dobset("08.07.2008");
	r1->setage(dobset);
	dobget = r1->getage();
	sprintf(ustr,"Требуется -> %s - получено -> %s",dobget.FormatString("yyyy.mm.dd"), dobset.FormatString("yyyy.mm.dd"));
	String uob=ustr;
	Check(dobget==dobset,uob);
}

void __fastcall TTestPerson::TestsetAge2() {
	// void setAge(TDate dob)
	String astr;
	r1->setAge("28.02.1983");
	astr = r1->getAge();
}

void __fastcall TTestPerson::TestgetName() {
	// AnsiString getName(int language)
}

void __fastcall TTestPerson::TestgetI() {
	// AnsiString getI(int language)
}

void __fastcall TTestPerson::TestgetSecondName() {
	// AnsiString getSecondName(int language)
}

void __fastcall TTestPerson::TestgetO() {
	// AnsiString getO(int language)
}

void __fastcall TTestPerson::TestgetSurName() {
	// AnsiString getSurName(int language)
}

void __fastcall TTestPerson::TestgetSURNAME() {
	// AnsiString getSURNAME(int language)
}

void __fastcall TTestPerson::TestgetFIO() {
	// AnsiString getFIO(int language)
}

void __fastcall TTestPerson::TestgetIOF() {
	// AnsiString getIOF(int language)
}

void __fastcall TTestPerson::TestgetFio() {
	// AnsiString getFio(int language)
}

void __fastcall TTestPerson::TestgetioF() {
	// AnsiString getioF(int language)
}

void __fastcall TTestPerson::TestsetName() {
	// void setName(int language, AnsiString name)
}

void __fastcall TTestPerson::TestsetSecondName() {
	// void setSecondName(int language, AnsiString secondname)
}

void __fastcall TTestPerson::TestsetSurName() {
	// void setSurName(int language, AnsiString surname)
}

void __fastcall TTestRacer::SetUp() {
}

void __fastcall TTestRacer::TearDown() {
}

void __fastcall TTestRacer::TestgetFIScode() {
	// AnsiString getFIScode()
}

void __fastcall TTestRacer::TestsetFIScode() {
	// void setFIScode(AnsiString sfis)
}

void __fastcall TTestRacer::TestsetPerson() {
	// void setPerson(Person *p)
}

void __fastcall TTestRacer::TestsetRacerName() {
	// void setRacerName(Person *p)
}

void __fastcall TTestRacer::TestsetRacerSecondName() {
	// void setRacerSecondName(Person *p)
}

void __fastcall TTestRacer::TestsetRacerSurName() {
	// void setRacerSurName(Person *p)
}

void __fastcall TTestRacer::TestsetRacerAge() {
	// void setRacerAge(Person *p)
}

static void registerTests() {
	Testframework::RegisterTest(TTestPerson::Suite());
	Testframework::RegisterTest(TTestRacer::Suite());

	r1 = new Racer;
	r1->setFIScode("123456");
	r1->setPerson(&p1);

}
#pragma startup registerTests 33
