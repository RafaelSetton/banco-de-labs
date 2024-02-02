escolha_sheila = input().lower()
escolha_reginaldo = input().lower()

if escolha_sheila == escolha_reginaldo:
    print('empate')
elif escolha_sheila == 'tesoura' and (escolha_reginaldo == 'papel' or escolha_reginaldo == 'lagarto'):
    print('Interestelar')
elif escolha_sheila == 'papel' and (escolha_reginaldo == 'pedra' or escolha_reginaldo == 'spock'):
    print('Interestelar')
elif escolha_sheila == 'pedra' and (escolha_reginaldo == 'lagarto' or escolha_reginaldo == 'tesoura'):
    print('Interestelar')
elif escolha_sheila == 'lagarto' and (escolha_reginaldo == 'spock' or escolha_reginaldo == 'papel'):
    print('Interestelar')
elif escolha_sheila == 'spock' and (escolha_reginaldo == 'tesoura' or escolha_reginaldo == 'pedra'):
    print('Interestelar')
else:
    print('Jornada nas Estrelas')




