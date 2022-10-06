#pragma once




// ������ģʽ
// ���ӿ�ת��Ϊ�ͻ���Ҫ�ӿ�����

namespace AdapterPattern
{
	void Entry();

	// ��������: ���ڼ̳�
	class ITarget
	{
	public:
		virtual void f1() {}
		virtual void f2() {}
		virtual void fc() {}
	};

	class Adaptee
	{
	public:
		void fa() { /*...*/ }
		void fb() { /*...*/ }
		void fc() { /*...*/ }
	};

	// private�̳�
	// ͨ��private�̳л��Adaptee��ʵ��Ч��������¶�����Ա
	// �������г�Ա��������Ա�����������еķ���Ȩ�ޱ�Ϊprivate�������ڳ�Ա�����з��ʻ���public��Ա������ͨ��������ʣ�
	class Adaptor: public ITarget, private Adaptee
	{
	public:
		void f1()override
		{
			Adaptee::fa();
		}
		void f2()override
		{
			//...����ʵ��f2()...
		}
		// ����fc()����Ҫʵ�֣�ֱ�Ӽ̳���Adaptee�����Ǹ��������������Ĳ�ͬ��
		void fc()override
		{
			Adaptee::fc();
		}
	};



	// �������������������
	class Adaptor2: public ITarget
	{
	private:
		Adaptee _adaptee;
  
	public:
		Adaptor2(Adaptee& adaptee) :_adaptee(adaptee) {}
  
		void f1()
		{
			_adaptee.fa(); //ί�и�Adaptee
		}
  
		void f2()
		{
			//...����ʵ��f2()...
		}
  
		void fc()
		{
			_adaptee.fc();
		}
	};

} // namespace AdapterPattern


// ����

/*
�����Žӡ�װ������������
�� 4 ��ģʽ�ǱȽϳ��õĽṹ�����ģʽ�����ǵĴ���ṹ�ǳ����ơ�
��ͳ��˵�����Ƕ����Գ�Ϊ Wrapper ģʽ��Ҳ����ͨ�� Wrapper ����η�װԭʼ�ࡣ
���� 4 �����ģʽ��������ȫ��ͬ��Ҳ����˵Ҫ��������⡢Ӧ�ó�����ͬ����Ҳ�����ǵ���Ҫ����

����ģʽ������ģʽ�ڲ��ı�ԭʼ��ӿڵ������£�Ϊԭʼ�ඨ��һ�������࣬��ҪĿ���ǿ��Ʒ��ʣ����Ǽ�ǿ���ܣ���������װ����ģʽ���Ĳ�ͬ��
�Ž�ģʽ���Ž�ģʽ��Ŀ���ǽ��ӿڲ��ֺ�ʵ�ֲ��ַ��룬�Ӷ������ǿ��Խ�Ϊ���ס�Ҳ��Զ����ؼ��Ըı䡣
װ����ģʽ��װ����ģʽ�ڲ��ı�ԭʼ��ӿڵ�����£���ԭʼ�๦�ܽ�����ǿ������֧�ֶ��װ������Ƕ��ʹ�á�
������ģʽ��������ģʽ��һ���º�Ĳ��Ȳ��ԡ��������ṩ��ԭʼ�಻ͬ�Ľӿڣ�������ģʽ��װ����ģʽ�ṩ�Ķ��Ǹ�ԭʼ����ͬ�Ľӿڡ�
*/