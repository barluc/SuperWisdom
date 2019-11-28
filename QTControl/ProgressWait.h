#pragma once

#include <QObject>


/**
 * �ȴ��������ؼ� ����:feiyangqingyun(QQ:517216493) 2016-10-28
 * 1:֧�ֶ��ֵȴ���ʽ��� Բ��״��� ��תԲ��� ����Բ�� ������� Բ�����
 * 2:�����÷�Χֵ�͵�ǰֵ
 * 3:������ǰ��ɫ����ɫ
 * 4:������˳ʱ����ʱ����ת
 * 5:֧�������С����
 * 6:֧��������ת�ٶȼ��
 */

#include <QWidget>

class ProgressWait : public QWidget
{
	Q_OBJECT
		Q_ENUMS(BarStyle)

		Q_PROPERTY(bool clockWise READ getClockWise WRITE setClockWise)
		Q_PROPERTY(bool showPercent READ getShowPercent WRITE setShowPercent)

		Q_PROPERTY(int currentValue READ getCurrentValue WRITE setCurrentValue)
		Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
		Q_PROPERTY(int interval READ getInterval WRITE setInterval)

		Q_PROPERTY(BarStyle barStyle READ getBarStyle WRITE setBarStyle)
		Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
		Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)
		Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

public:
	enum BarStyle {
		BarStyle_Arc = 0,           //Բ��״���
		BarStyle_RoundCircle = 1,   //��תԲ���
		BarStyle_Pie = 2,           //����Բ�����
		BarStyle_Line = 3,          //�������
		BarStyle_Ring = 4,          //Բ�����
		BarStyle_SingleCircle = 5,  //һ��Բ��˸
		BarStyle_DoubleCircle = 6   //����Բ��˸
	};

	ProgressWait(QWidget *parent = 0);
	~ProgressWait();

protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
	void drawArc(QPainter *painter);
	void drawRoundCircle(QPainter *painter);
	void drawPie(QPainter *painter);
	void drawLine(QPainter *painter);
	void drawRing(QPainter *painter);
	void drawSingleCircle(QPainter *painter);
	void drawDoubleCircle(QPainter *painter);
	void drawValue(QPainter *painter);

private:
	bool clockWise;                 //˳ʱ����ʱ��
	bool showPercent;               //��ʾ��ǰ�ٷֱ�
	int currentValue;               //��ǰֵ
	int maxValue;                   //���ֵ
	int interval;                   //��ת���

	int minRadius;                  //��С�뾶
	int maxRadius;                  //���뾶
	int offsetRadius;               //�뾶ƫ����
	int leftRadius;                 //���Բ�뾶
	int rightRadius;                //�ұ�Բ�뾶
	bool leftIncrease;              //��ߵ���
	bool rightIncrease;             //�ұߵ���

	BarStyle barStyle;              //��ʽ
	QColor background;              //����ɫ
	QColor foreground;              //ǰ��ɫ
	QColor textColor;               //������ɫ

	QTimer *timer;                  //��ʱ������

private:
	double degreesToRadians(double value);

private slots:
	void updateValue();

public:
	bool getClockWise()             const;
	bool getShowPercent()           const;
	int getCurrentValue()           const;
	int getMaxValue()               const;
	int getInterval()               const;

	BarStyle getBarStyle()          const;
	QColor getBackground()          const;
	QColor getForeground()          const;
	QColor getTextColor()           const;

	QSize sizeHint()                const;
	QSize minimumSizeHint()         const;

public Q_SLOTS:
	//����˳ʱ����ʱ����ת
	void setClockWise(bool clockWise);
	//�����Ƿ���ʾ�ٷֱ�
	void setShowPercent(bool showPercent);
	//���õ�ǰֵ
	void setCurrentValue(int currentValue);
	//�������ֵ
	void setMaxValue(int maxValue);
	//������ת�ٶȼ��
	void setInterval(int interval);

	//������ʽ
	void setBarStyle(const BarStyle &barStyle);
	//����ǰ��ɫ
	void setBackground(const QColor &background);
	//����ǰ��ɫ
	void setForeground(const QColor &foreground);
	//����������ɫ
	void setTextColor(const QColor &textColor);
};
