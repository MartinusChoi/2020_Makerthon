from oauth2client.service_account import ServiceAccountCredentials
import gspread
import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
from sklearn.linear_model import LinearRegression

data_length_before = 0
data_length_current = 0

scope = ['https://spreadsheets.google.com/feeds',
         'https://www.googleapis.com/auth/drive']
credentials = ServiceAccountCredentials.from_json_keyfile_name(
        'C:\\Users\\marti\\PycharmProjects\\SampleSheet\\pillit-483a1499da53.json', scope)
gc = gspread.authorize(credentials)


while True:
    # 스프레드 시트 연동하기
    gc1 = gc.open("pillit2").worksheet('복용데이터')
    gc2 = gc1.get_all_values()
    gc3 = gc.open("pillit2").worksheet('AI복용주기')

    # 스프레드 시트로부터 가져온 복용 데이터를 Pandas Dataframe으로 변환
    gc2 = pd.DataFrame(gc2, columns=gc2[0])
    gc2 = gc2.reindex(gc2.index.drop(0))

    data_length_current = len(gc2)

    # 이전에 학습을 수행한 데이터의 길이보다 현재 데이터의 길이가 더 늘어나면 학습 수행
    # 즉, 데이터가 추가되면 다시 학습을 수행
    if data_length_before < data_length_current:

        # 이전 데이터 길이 저장
        data_length_before = data_length_current

        # 학습에 이용하기 위해 타임스탬프 -> 초단위 정수로 변환
        for i in range(len(gc2)):
            str = gc2.iloc[i][0]
            str = str.split(' ')

            if (str[3] == '오전'):
                only_time = str[4]
                only_time = only_time.split(':')

                hour = int(only_time[0])
                minute = int(only_time[1])
                second = int(only_time[2])

                hour = hour * 60 * 60
                minute = minute * 60
                total_second = hour + minute + second

                gc2.iloc[i][0] = total_second

            elif (str[3] == '오후'):
                only_time = str[4]
                only_time = only_time.split(':')

                hour = int(only_time[0])
                minute = int(only_time[1])
                second = int(only_time[2])

                hour = hour + 12
                hour = hour * 60 * 60
                minute = minute * 60
                total_second = hour + minute + second

                gc2.iloc[i][0] = total_second

        # 데이터 분할
        X = gc2['칸']
        y_train = np.array(gc2['타임스탬프'])
        x = np.array(['a', 'b', 'c'])

        # 카테고리 실수화
        classle = LabelEncoder()

        X_train = classle.fit_transform(X)
        x_test = classle.fit_transform(x)

        # 데이터 reshaping
        X_train = X_train.reshape(-1, 1)

        y_train = y_train.reshape(-1, 1)

        x_test = x_test.reshape(-1, 1)

        # 모델 학습
        lr = LinearRegression()

        lr.fit(X_train, y_train)

        y_train_pred = lr.predict(X_train)
        predict = lr.predict(x_test)

        # 예측 결과 실수화
        num1 = predict[0][0]
        num2 = predict[1][0]
        num3 = predict[2][0]

        num1 = round(num1)
        num2 = round(num2)
        num3 = round(num3)

        # a칸을 주로 복용한 시간 작성
        hour = num1 // 3600
        num1 = num1 % 3600
        minute = num1 // 60
        num1 = num1 % 60
        second = num1
        noon = "오전"

        if hour > 12:
            hour = hour - 12
            noon = "오후"

        hour = repr(hour)
        if minute % 10 == 0:
            minute = '0' + repr(minute)
        else:
            minute = repr(minute)
        second = repr(second)

        time_stamp = noon + " " + hour + ':' + minute + ':' + second

        gc3.update_acell('B2', time_stamp)

        # b칸을 주로 복용한 시간 작성
        hour = num2 // 3600
        num2 = num2 % 3600
        minute = num2 // 60
        num2 = num2 % 60
        second = num2
        noon = "오전"

        if hour > 12:
            hour = hour - 12
            noon = "오후"

        hour = repr(hour)
        if minute % 10 == 0:
            minute = '0' + repr(minute)
        else:
            minute = repr(minute)
        second = repr(second)

        time_stamp = noon + ' ' + hour + ':' + minute + ':' + second

        gc3.update_acell('B3', time_stamp)

        # c칸을 주로 복용한 시간 작성
        hour = num3 // 3600
        num3 = num3 % 3600
        minute = num3 // 60
        num3 = num3 % 60
        second = num3
        noon = "오전"

        if hour > 12:
            hour = hour - 12
            noon = "오후"

        hour = repr(hour)
        if minute % 10 == 0:
            minute = '0' + repr(minute)
        else:
            minute = repr(minute)
        second = repr(second)

        time_stamp = noon + ' ' + hour + ':' + minute + ':' + second

        gc3.update_acell('B4', time_stamp)
