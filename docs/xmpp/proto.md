# 登录

```bash
curl 'https://meet.chuanshaninfo.com/api/ua/passport/login' \
-X POST \
-H 'Accept: application/json, text/plain, */*' \
-H 'Content-Type: application/json' \
--data-raw '{"loginId":"18910221510","password":"200791"}'

{
  "type": "success",
  "data": "22256927-da29-4a3d-9170-08890a6d45c5",
  "msg": "登录成功",
  "extra": {},
  "warn": false,
  "verify": false,
  "success": true,
  "error": false
}
```

# 功能接收

```xml

<iq to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    id='ada529ea6bb33da70a60d20adf2824872fa612d50000000b' type='result'
    from='lobby.meet.chuanshaninfo.com'>
    <query xmlns='http://jabber.org/protocol/disco#info'>
        <identity category='conference' type='text' name='Prosody Chatrooms'/>
        <feature var='http://jabber.org/protocol/muc'/>
        <feature var='http://jabber.org/protocol/muc#unique'/>
        <feature var='http://jabber.org/protocol/disco#info'/>
        <feature var='http://jabber.org/protocol/disco#items'/>
        <feature var='http://jabber.org/protocol/commands'/>
    </query>
</iq>

<iq to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    id='ada529ea6bb33da70a60d20adf2824872fa612d50000000d' type='error'
    from='speakerstats.meet.chuanshaninfo.com'>
<error type='cancel'>
    <service-unavailable xmlns='urn:ietf:params:xml:ns:xmpp-stanzas'/>
</error>
</iq>

<iq to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    id='ada529ea6bb33da70a60d20adf2824872fa612d50000000e' type='result'
    from='pubsub.meet.chuanshaninfo.com'>
<query xmlns='http://jabber.org/protocol/disco#info'>
    <identity category='pubsub' type='service' name='Prosody PubSub Service'/>
    <feature var='http://jabber.org/protocol/pubsub'/>
    <feature var='http://jabber.org/protocol/pubsub#multi-items'/>
    <feature var='http://jabber.org/protocol/pubsub#delete-items'/>
    <feature var='http://jabber.org/protocol/pubsub#outcast-affiliation'/>
    <feature var='http://jabber.org/protocol/pubsub#purge-nodes'/>
    <feature var='http://jabber.org/protocol/pubsub#create-nodes'/>
    <feature var='http://jabber.org/protocol/pubsub#retrieve-subscriptions'/>
    <feature var='http://jabber.org/protocol/pubsub#meta-data'/>
    <feature var='http://jabber.org/protocol/pubsub#retract-items'/>
    <feature var='http://jabber.org/protocol/pubsub#publish'/>
    <feature var='http://jabber.org/protocol/pubsub#item-ids'/>
    <feature var='http://jabber.org/protocol/pubsub#subscription-options'/>
    <feature var='http://jabber.org/protocol/pubsub#instant-nodes'/>
    <feature var='http://jabber.org/protocol/pubsub#create-and-configure'/>
    <feature var='http://jabber.org/protocol/pubsub#retrieve-items'/>
    <feature var='http://jabber.org/protocol/pubsub#auto-create'/>
    <feature var='http://jabber.org/protocol/pubsub#config-node'/>
    <feature var='http://jabber.org/protocol/pubsub#subscribe'/>
    <feature var='http://jabber.org/protocol/pubsub#access-open'/>
    <feature var='http://jabber.org/protocol/pubsub#persistent-items'/>
    <feature var='http://jabber.org/protocol/pubsub#member-affiliation'/>
    <feature var='http://jabber.org/protocol/pubsub#modify-affiliations'/>
    <feature var='http://jabber.org/protocol/pubsub#publisher-affiliation'/>
    <feature var='http://jabber.org/protocol/pubsub#retrieve-default'/>
    <feature var='http://jabber.org/protocol/pubsub#delete-nodes'/>
    <feature var='http://jabber.org/protocol/pubsub#publish-options'/>
    <feature var='http://jabber.org/protocol/disco#info'/>
    <feature var='http://jabber.org/protocol/disco#items'/>
</query>
</iq>

<iq to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    id='ada529ea6bb33da70a60d20adf2824872fa612d50000000f'
    type='result'
    from='auth.meet.chuanshaninfo.com'>
<query xmlns='http://jabber.org/protocol/disco#info'>
    <identity category='server' type='im' name='Prosody'/>
    <identity category='pubsub' type='pep' name='Prosody'/>
    <feature var='urn:xmpp:ping'/>
    <feature var='jabber:iq:version'/>
    <feature var='msgoffline'/>
    <feature var='vcard-temp'/>
    <feature var='jabber:iq:register'/>
    <feature var='urn:xmpp:time'/>
    <feature var='jabber:iq:time'/>
    <feature var='jabber:iq:last'/>
    <feature var='jabber:iq:private'/>
    <feature var='http://jabber.org/protocol/disco#info'/>
    <feature var='http://jabber.org/protocol/disco#items'/>
    <feature var='http://jabber.org/protocol/pubsub#publish'/>
    <feature var='jabber:iq:roster'/>
    <feature var='urn:xmpp:carbons:2'/>
    <feature var='urn:xmpp:blocking'/>
    <feature var='http://jabber.org/protocol/commands'/>
</query>
</iq>

<iq to='conference.meet.chuanshaninfo.com'
    id='ada529ea6bb33da70a60d20adf2824872fa612d500000010'
    type='error'
    from='conferenceduration.meet.chuanshaninfo.com'>
<error type='cancel'>
    <service-unavailable xmlns='urn:ietf:params:xml:ns:xmpp-stanzas'/>
</error>
</iq>

<iq from='focus.meet.chuanshaninfo.com'
    id='ada529ea6bb33da70a60d20adf2824872fa612d50000000c'
    type='result'
    to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'>
<query xmlns='http://jabber.org/protocol/disco#info'>
    <identity name='Jitsi Meet Focus' category='component' type='generic'/>
    <feature var='http://jabber.org/protocol/disco#info'/>
    <feature var='urn:xmpp:ping'/>
    <feature var='jabber:iq:last'/>
    <feature var='urn:xmpp:time'/>
    <feature var='http://jitsi.org/protocol/focus'/>
</query>
</iq>
```

# 消息处理

## 加密消息
### OMEMO
- 订阅设备列表
```xml
<message type='headline' to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
         from='18910221510@meet.chuanshaninfo.com'>
    <event xmlns='http://jabber.org/protocol/pubsub#event'>
        <items node='eu.siacs.conversations.axolotl.devicelist'>
            <item id='current'>
                <list xmlns='eu.siacs.conversations.axolotl'>
                    <device id='1229772742'/>
                    <device id='27590415'/>
                    <device id='871820715'/>
                </list>
            </item>
        </items>
    </event>
</message>
``` 
- 添加设备ID
```xml

<message type='headline'
         to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
         from='18510248810@meet.chuanshaninfo.com'>
    <event xmlns='http://jabber.org/protocol/pubsub#event'>
        <items node='eu.siacs.conversations.axolotl.devicelist'>
            <item id='075e9a14-f544-4a93-a241-75185200babe'>
                <list xmlns='eu.siacs.conversations.axolotl'>
                    <device id='1555855859'/>
                    <device id='1893086516'/>
                    <device id='1681766854'/>
                    <device id='1889961110'/>
                    <device id='1974130221'/>
                </list>
            </item>
        </items>
    </event>
</message>
```

- 绑定设备

```xml
<iq to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' 
    id='' 
    type='result'>
    <pubsub xmlns='http://jabber.org/protocol/pubsub'>
        <items node='eu.siacs.conversations.axolotl.bundles:1974130221'>
            <item xmlns='http://jabber.org/protocol/pubsub' id='current'>
                <bundle xmlns='eu.siacs.conversations.axolotl'>
                    <signedPreKeyPublic signedPreKeyId='40802'>BROQBBMCBBXhrCkD6x6m9zW16+oVjYDvj6WTarkjCUtr
                    </signedPreKeyPublic>
                    <signedPreKeySignature>
                        WFOPN/BhTJ9ckVDt72DFcL7fJ2nlToiN4SISKaf2YeluwpGtJfea0gLmcsVZCXbuAzxMLQS7hmQxYTtIZm7iAA==
                    </signedPreKeySignature>
                    <identityKey>BXZo0zcLKX5loye0Oqszs0u3/Q1/x/3+tJxTuZiBNIIt</identityKey>
                    <prekeys>
                        <preKeyPublic preKeyId='13180940'>BYOjgPTqfWqKy0V9jmF36eeZE0B7WE2gCJkVbZKqly9b</preKeyPublic>
                        <preKeyPublic preKeyId='13180941'>BVDUtCDmnAxHMUpl5FEdPt6ipyK7z5DcbuPAnYZtWWAY</preKeyPublic>
                        <preKeyPublic preKeyId='13180942'>BYbezhe6Np6MugIu0nY7gFAuZ90R4qvMMEUjo0yjxSIq</preKeyPublic>
                        <preKeyPublic preKeyId='13180943'>BRF4h9DGXASxxiTYnNQqF1Pe32YrXh042S4yaWCqzZZB</preKeyPublic>
                        <preKeyPublic preKeyId='13180944'>BVmaUEpMYAmQjsppzcgapeHdZx/+tCw3fRgXR0z8uB9u</preKeyPublic>
                        <preKeyPublic preKeyId='13180945'>BS37t9USbtibMvmHMkYNwk6SDlTfUESiW9i1NLGxEjxb</preKeyPublic>
                        <preKeyPublic preKeyId='13180946'>BSJgs7ucgQftd5ZcdA2u6UlAzrTCrvf5iCITni/IPRs0</preKeyPublic>
                        <preKeyPublic preKeyId='13180947'>BefvSLcOqGTKBqMru8/0rywXCssoU8pvKr1tsO90MydC</preKeyPublic>
                        <preKeyPublic preKeyId='13180948'>BWUPTEgf9yn7NeA8KAdp1PzOyQkStd9c+2l0zazgpHRH</preKeyPublic>
                        <preKeyPublic preKeyId='13180949'>BQ1OQFAjGFw0wyhzDwV/G3qdoMyXWuSwzoLvdQyKnHch</preKeyPublic>
                        <preKeyPublic preKeyId='13180950'>BS2765Q9Cw8g/cLJGYiJt/LrRopn8UPufIJb/UluQgAs</preKeyPublic>
                        <preKeyPublic preKeyId='13180951'>Bak9YjIwgP3wvgybxTff5GMmLu3Z1tMSSJRXCJndmchq</preKeyPublic>
                        <preKeyPublic preKeyId='13180952'>BVYbOjUBlh27CSLSpv48ri9AttIxgDxDqJkqa1ZNCLs9</preKeyPublic>
                        <preKeyPublic preKeyId='13180953'>BdfQkDe08EutCvkeR9vDN/iWFMPyiT5R3mVA0Jfpi+VU</preKeyPublic>
                        <preKeyPublic preKeyId='13180954'>BQ6rrNNgglPmHz6WTi3/w58Krts4xilugAXvkvoIXQEz</preKeyPublic>
                        <preKeyPublic preKeyId='13180955'>Bfy9VMK2OndZF8I0Eg8rnfWEeDYU2Tpiu8MXStwfCSYQ</preKeyPublic>
                        <preKeyPublic preKeyId='13180956'>BTzG6P1Kr7NIYs8JCXgNH3G1nq46kfBFfs1K40a7QV0K</preKeyPublic>
                        <preKeyPublic preKeyId='13180957'>Bf5g/k8aOEtCecK09luz5/mlRwviV3fronnkvqS2P3lo</preKeyPublic>
                        <preKeyPublic preKeyId='13180958'>BUGynVsgx+FF8HOo+rxPMV4BPDOb8ckAY7jfABb5+Y1b</preKeyPublic>
                        <preKeyPublic preKeyId='13180959'>Bb9x0b7Ngad7zgIEpqe+VDeng8OzqPVn+oAzN5SFq7AO</preKeyPublic>
                        <preKeyPublic preKeyId='13180960'>BfLgm1mn/Thtm8VyIF9VvbppXwEZCRXBe5PhfUXB6bhF</preKeyPublic>
                        <preKeyPublic preKeyId='13180961'>BS5Eew5RHZVW0MRCFnJBFOtL6259qaugaRkP2pQdywFf</preKeyPublic>
                        <preKeyPublic preKeyId='13180962'>BU/KYu20SXysHyvWlDCtGO3aeJ9sIgdq+XhRZewLIhkZ</preKeyPublic>
                        <preKeyPublic preKeyId='13180963'>BVksn7qUuSznLvfyELNd/pBykpSc1sN6dvGfb4zplqdC</preKeyPublic>
                        <preKeyPublic preKeyId='13180964'>Bc1OAl/3Sxa+5VkQIWVwb1lkxs4HrEeTodHQO+nP5Htc</preKeyPublic>
                        <preKeyPublic preKeyId='13180965'>BVVxZSrUiXEY+3pBNHt8+vajU3x77o+8GeX4CF9macUH</preKeyPublic>
                        <preKeyPublic preKeyId='13180966'>Baw0inaWu4j1J7gGM7Ljyb8FW08rB/gNJ1jFS8M8oXpD</preKeyPublic>
                        <preKeyPublic preKeyId='13180967'>BfaBeB0kVmEZeR8zEyJpQx2Vxdsz85wj4AMgEffon8Nm</preKeyPublic>
                        <preKeyPublic preKeyId='13180968'>Ba8opOcUtZUY0rZTBgB/Y8P+tA++a3Xkyc28y7Qyfq11</preKeyPublic>
                        <preKeyPublic preKeyId='13180969'>BTBfEr6LLo1x49B/gfeDt0J8UbsMkKMHO/WnKf+DfLQ8</preKeyPublic>
                        <preKeyPublic preKeyId='13180970'>BUMUxBTEmN48SthIb0dzAOaGa5+agLgcrTsMQlO5TuYS</preKeyPublic>
                        <preKeyPublic preKeyId='13180971'>BTNEVyLS+OyrPtndn7rjfTSAejURseqrX87I0bBtWS8F</preKeyPublic>
                        <preKeyPublic preKeyId='13180972'>BeSTF5gQAz+MgNRvelVpPxC3p8Ud5jzsAexsWqoVZSQF</preKeyPublic>
                        <preKeyPublic preKeyId='13180973'>BatHKvR2FaX0ba5JAt68QUPMfaq6Nkn6W2Pr25DMZxpt</preKeyPublic>
                        <preKeyPublic preKeyId='13180974'>BUwWqGwth4YSp10P9/EkyJ3STfG9ktVAixzCSsU/dC1b</preKeyPublic>
                        <preKeyPublic preKeyId='13180975'>BRlV1/4HVWXel/mMvB80fxsgBDQGy4Z2JizfIYfcxVlR</preKeyPublic>
                        <preKeyPublic preKeyId='13180976'>BR8ErSi3Vtm83keN4SCu9saF8GNWg+FMWpxX8y+pyzQO</preKeyPublic>
                        <preKeyPublic preKeyId='13180977'>BRLZnal/OyknevOHdqI/r3QaH3F7HFaD8mPvVLRXQlJ5</preKeyPublic>
                        <preKeyPublic preKeyId='13180978'>BXxPq8ilrTwvHOIFo3ARsFLc1J0JbF9CPM4MWMdK8vZN</preKeyPublic>
                        <preKeyPublic preKeyId='13180979'>Ba9ra0pVsroSX+P058UzehPNwv2B5V1Q4JcESIQQ+oZv</preKeyPublic>
                        <preKeyPublic preKeyId='13180980'>BQKIIMkfNWi5O87S+Q2eoJ17rXF7HNGJLxNDret+FvA2</preKeyPublic>
                        <preKeyPublic preKeyId='13180981'>BfLDon/+uCWfjsz8olARGB7XCK5Kzny5DE3UwzGjhThB</preKeyPublic>
                        <preKeyPublic preKeyId='13180982'>BaDNpsdJUXWRTwMUkysZv4sIUSqNxmF7hA/IIzBQ0O4F</preKeyPublic>
                        <preKeyPublic preKeyId='13180983'>BYpxMLbvMAPCCn3p0jVI/qGvGBcHthbsh/a4ozPeo9YP</preKeyPublic>
                        <preKeyPublic preKeyId='13180984'>BR0WCQv+nBNRErFLRW2nESCxREL8kHI2wzk9gotaqTs0</preKeyPublic>
                        <preKeyPublic preKeyId='13180985'>BYec0TIKWVuO3ftML1o3xAw6C3Nq2E8teSlqKInRzLBv</preKeyPublic>
                        <preKeyPublic preKeyId='13180986'>Ba2ubMF0KW1NSsN2e4yhbI396VvUOl0LJ0+H17rhNvtN</preKeyPublic>
                        <preKeyPublic preKeyId='13180987'>BQnbp+O47FdwAYt+dsd2fkwMbDsABpgkY0A0DsqDyZMY</preKeyPublic>
                        <preKeyPublic preKeyId='13180988'>BcUfksdqePUj6M8upGjgEUGeV81LRsOsJO45inucBoZq</preKeyPublic>
                        <preKeyPublic preKeyId='13180989'>BR+J4A2iRkxAiNp4XmTrxNaOsym4xUM4yFQZUbj2Pg88</preKeyPublic>
                        <preKeyPublic preKeyId='13180990'>BQA066XC9V2eUNGrLveFKVJdZhqzhWqYo71cvbE0uOxw</preKeyPublic>
                        <preKeyPublic preKeyId='13180991'>BSc7JNpJm7GlREUwD7KlRjlTqMIN/+0EaE1NuX4cJ64b</preKeyPublic>
                        <preKeyPublic preKeyId='13180992'>BSdDI11F17fx09MDLEMPRsyQ2tWj2N/T0hUmWtWMDQdT</preKeyPublic>
                        <preKeyPublic preKeyId='13180993'>BQWw9mvAkyaBKkuriHGAK/RCf15nw1PC4/01h5xScrRW</preKeyPublic>
                        <preKeyPublic preKeyId='13180994'>BccDov/UVAE70DJWNjNGny8sDRjYGeK/EXyWj+EU48dy</preKeyPublic>
                        <preKeyPublic preKeyId='13180995'>BargjvB8d8+Fsn/MNFDpGRHD3Ns/K39LDR78Y4W3D2cn</preKeyPublic>
                        <preKeyPublic preKeyId='13180996'>BfQ/iWMMqs5bOe8BnmiKj7oipjGb+pk+ivdl/J0BgOM8</preKeyPublic>
                        <preKeyPublic preKeyId='13180997'>BczsTXrXSvmTS4Q5XLNrw8VYG3+SgB0/mHULDSMAI8NR</preKeyPublic>
                        <preKeyPublic preKeyId='13180998'>BTv/VqrL2Z/euyvep2pnxV3ocC4I3xQ9z61G7S9nhABm</preKeyPublic>
                        <preKeyPublic preKeyId='13180999'>Bbh/0Beb+W709/23V4FV1mBpzIGEdZQsWnqUU5nJcCY3</preKeyPublic>
                        <preKeyPublic preKeyId='13181000'>BWWGFrbpOuuU9maGURfsrlQOsqoGkM+BZLMZKYy2NHRq</preKeyPublic>
                        <preKeyPublic preKeyId='13181001'>BaQUlwe1mxdmX2rQH0i0AOP7yaxa5vzLUgZLt861F/BF</preKeyPublic>
                        <preKeyPublic preKeyId='13181002'>Bc/X1+omu+Bty6X4ilPQXUxtoxW8XbgrGymDt9uGqn4R</preKeyPublic>
                        <preKeyPublic preKeyId='13181003'>BY2xLyr/r1FXaiE2jTWAo8FP1p8erIvEbGmKUNBwZhYX</preKeyPublic>
                        <preKeyPublic preKeyId='13181004'>BZ+EteRcDelbZzmX+Uzf/MHJGj6e/ZTOaq6QXU6RCwYS</preKeyPublic>
                        <preKeyPublic preKeyId='13181005'>BfpL7YJSqV+zu2c13BGQ1B7N4O/mD/XRQfre06A/1PEv</preKeyPublic>
                        <preKeyPublic preKeyId='13181006'>BVflFcD4Ib+UjUI9am4lkXxcRYD8BlZ8QTLkONzXdO0h</preKeyPublic>
                        <preKeyPublic preKeyId='13181007'>BanXuBo4iL/bXFacwwYePYnZoI+WLIVUnuEeFXlpehoV</preKeyPublic>
                        <preKeyPublic preKeyId='13181008'>BW2ZWck7y6TeyF7k95VutNCD2bjek3ipoRNsf9dQQ6Iv</preKeyPublic>
                        <preKeyPublic preKeyId='13181009'>BQpfA+Z3ml/tvtAaTPcWvNXHPV+9sGywl8Ef9yx28NQ1</preKeyPublic>
                        <preKeyPublic preKeyId='13181010'>BUUV3yKt+QSpFkwq3nOgiw0nFmDP86IYjNXKOTnNg7AT</preKeyPublic>
                        <preKeyPublic preKeyId='13181011'>Ba/s3Wf3x6clip0epqyJ9I/mYT6JdrZAekhWSS7ePAVx</preKeyPublic>
                        <preKeyPublic preKeyId='13181012'>BQEJkWzlYHl/aat/fRdCNp8Knxc1ZXHiKpHo/5uJNylO</preKeyPublic>
                        <preKeyPublic preKeyId='13181013'>BU1ZEI7Yk19PcJVKaql1gXBen7XalzlthkL1d7V/N6N/</preKeyPublic>
                        <preKeyPublic preKeyId='13181014'>Bf3FXQQaFEiQIapq/WsVfuHTgRObzngPMnm22XUnTOUR</preKeyPublic>
                        <preKeyPublic preKeyId='13181015'>BZ7G/7YGM0YcLw7fICONNAvSyQpnNiNaNAfSBJzfKeod</preKeyPublic>
                        <preKeyPublic preKeyId='13181016'>BSCNFfHkEmRPxfaFNtjfaOeRQzAMHoDmGrRfbrVswzJd</preKeyPublic>
                        <preKeyPublic preKeyId='13181017'>BeYd9DN2iVbPdUapWiWsgZ/HemzD5oN51wRtAh9Q0xZy</preKeyPublic>
                        <preKeyPublic preKeyId='13181018'>BXPm5AN62ivxGAXD0v5ERdxrTfWRIorZ2Guw+Lb9JP59</preKeyPublic>
                        <preKeyPublic preKeyId='13181019'>BSBahuEagg+ZA81TJcPOWp0+EC904UpgxFE2ik+UWmI4</preKeyPublic>
                        <preKeyPublic preKeyId='13181020'>Bevnw6AhF2Bao6ZKccxYCyQvXIDUAF+ZEQiRPNPs6UEL</preKeyPublic>
                        <preKeyPublic preKeyId='13181021'>Bc3TiHZZLBH7kvzgKNJmmK+kbNZocqAk/KzaW6Rz6EQu</preKeyPublic>
                        <preKeyPublic preKeyId='13181022'>BZXPvMLlK5oVODNm3WE+KeoJKNMDcVO9U8Voav4zdnRC</preKeyPublic>
                        <preKeyPublic preKeyId='13181023'>BbMY6X234uDHBFbKTTW29THMU0hiI1W2VJwwl/xITcQU</preKeyPublic>
                        <preKeyPublic preKeyId='13181024'>BdmrfYbC6E5zkYKGICAi0yeCL7FTwTSerJAalf8+J9NP</preKeyPublic>
                        <preKeyPublic preKeyId='13181025'>BS00mlmxLQcZnSxQGPH55/CrVuZoalng6IKgz/Bz808A</preKeyPublic>
                        <preKeyPublic preKeyId='13181026'>BapMbhHwpwQostCCd6m2X8Q7F3Zy+kgGHdT6QCH3PJAf</preKeyPublic>
                        <preKeyPublic preKeyId='13181027'>BanWgDJydEF/sNdtCwov0a7Hb8fWY5mixjdFf9ZX7/gi</preKeyPublic>
                        <preKeyPublic preKeyId='13181028'>BW/6/Sme60y1/Zqa3C7k56RLpJTDg4N1Xb+2h+d0aD0G</preKeyPublic>
                        <preKeyPublic preKeyId='13181029'>BXhxsY/fZNwWatl9e3y5qprQRzZhKiTtI1uHMi6RkNkB</preKeyPublic>
                        <preKeyPublic preKeyId='13181030'>BdsVejenJtRb0UIhUECTxDx7tjiQIprJMlrjmgWOIgcX</preKeyPublic>
                        <preKeyPublic preKeyId='13181031'>BUhVzu/ExrRY5ALHI3V7Qk9iEd/wMmIcY4DbzDmtNVlA</preKeyPublic>
                        <preKeyPublic preKeyId='13181032'>BY/rFufItR0J/soTUO4dDRGziCbhUhMS/4YSlIZ09FJ7</preKeyPublic>
                        <preKeyPublic preKeyId='13181033'>BeH+GYWnsByx6eFI/VqqkMahOEDdPRk1jpHw2k1fvF1X</preKeyPublic>
                        <preKeyPublic preKeyId='13181034'>BYeLnWkrJd/XcAUsQ5cgXBl8dTWjSJbugMxSBo9gCN0y</preKeyPublic>
                        <preKeyPublic preKeyId='13181035'>BSAJzmvPWGP0QQov7DciccLIIgLqiv9xW0qBwsTSoMM0</preKeyPublic>
                        <preKeyPublic preKeyId='13181036'>BQascmOVx8hglM+s7SPjxXyFG4lobJCJKscrVBn2ENNf</preKeyPublic>
                        <preKeyPublic preKeyId='13181037'>BTRCY/fIBgd9q3Pjt9QFjgWlGFPD7t/dr8Iy1CagKgoG</preKeyPublic>
                        <preKeyPublic preKeyId='13181038'>BbYRo8ZV4+dAncfjv1O9CasdIBmksCWQlelRwjXA1rpu</preKeyPublic>
                        <preKeyPublic preKeyId='13181039'>BUsbgSHsnqgLO6nXO3YGao9pOBn/ETWayJXZ2QB8kMpd</preKeyPublic>
                    </prekeys>
                </bundle>
            </item>
        </items>
    </pubsub>
</iq>
```
- 构建会话
```xml

<iq id='' 
    from='18510248810@meet.chuanshaninfo.com'
    to='18510248810@meet.chuanshaninfo.com' 
    type='get'>
    <pubsub xmlns='http://jabber.org/protocol/pubsub'>
        <items node='eu.siacs.conversations.axolotl.bundles:1974130221'/>
    </pubsub>
</iq>
```

- 发送加密消息
```xml
<message type='chat' id='26338626-82b7-48f1-8951-5ce7b9c49d99' 
         to='18910221510@meet.chuanshaninfo.com'
         from='13661358184@meet.chuanshaninfo.com/monocles chat[1.6.4].O8Ve'>
    <body>I sent you an OMEMO encrypted message 
        but your client doesn’t seem to support that. 
        Find more information on
        https://conversations.im/omemo
    </body>
    <encrypted xmlns='eu.siacs.conversations.axolotl'>
        <header sid='729031887'>
            <key prekey='true' rid='1541878781'>
                MwhPEiEFpmm7y7BjZlff/W3sRcBPjM8mYoymu5UBjm6F++PFkmQaIQVKs23++iZHxyK5j0itzbJh8Wc6NyASqxGvVZZWirsNdiJiMwohBUtPHx4lgKpNVf2x0RBY3/44mNqxylmcyayt4GQhW7UwEAsYACIw4WiEib0DDh98jWlnEg0ZuEnyX0jlwRORcmfNhgnKWwO8uyudNi0XJCYC810G3tI6qRY2OOhjtTYoz8nQ2wIwAQ==
            </key>
            <key prekey='true' rid='871820715'>
                MwgfEiEF9VXq9EfgXamayAG8I1t1St/RZPKnSQDpPIFv3beu6DAaIQVKs23++iZHxyK5j0itzbJh8Wc6NyASqxGvVZZWirsNdiJiMwohBQmH2vKQ3wt+0jzAvkSrpHM8F4wsUqw1UfhwvaygCSRoEAsYACIwVzKeFWVM9i6Eh4UIoanqOKE5sJ1P6630Wf3At/6h17rFuVZfYGt27aNHxmXbvl4NkimpsVAdgzEoz8nQ2wIwAQ==
            </key>
            <key prekey='true' rid='1229772742'>
                Mwg/EiEFKvYXQ5Cs++kVQUNkpHhIJ2EHrnVMIMK4J8j91TePMWgaIQVKs23++iZHxyK5j0itzbJh8Wc6NyASqxGvVZZWirsNdiJiMwohBYLBPR7SQ0DgDtZ7yo4nPYLaKmqig8mtK5wpCrR2bHEHEAYYACIwAYtQOlzmmvRWvAhnh8b1oiiY3j/T7I83MerD6PvhC6woBPMuqyHLsBuKMuIsAFpaIkEGyOyk+Kgoz8nQ2wIwAQ==
            </key>
            <key prekey='true' rid='193624368'>
                MwhcEiEFXxxmdK0bizwpjZaSSTnBztEuT94V9Ax+7BHgvo660B0aIQVKs23++iZHxyK5j0itzbJh8Wc6NyASqxGvVZZWirsNdiJiMwohBcF5gVjxPjAD39BcqQTT5O1IkXnUYJatj9iOqbVxvF01EAsYACIwJFlBdyjPxg7PML3ebjJ8m/Vs0OT/FZl4LUuCDjyQVmnuXtCju4Hi23SN3lV0VPq7wb3kZFX1AdEoz8nQ2wIwAQ==
            </key>
            <key prekey='true' rid='1288001621'>
                MwgyEiEF8FVQIdIOLPeZrsEUHux1IQJOI0NeLN9dygIjFVz2gE8aIQVKs23++iZHxyK5j0itzbJh8Wc6NyASqxGvVZZWirsNdiJiMwohBfFB7VMEMiPmhESwyxeXrn1k/INPL7vMz2YCt900rChKEAsYACIw9zTtGDzb+DZ3B3jFa8WdxF/KCysBCV0HyTEjm/O9Un+A1NW9hjc9j0IQy/hwKoJoUGIXuDfCWycoz8nQ2wIwAQ==
            </key>
            <iv>w3z+sEgZ1ofBoH3R</iv>
        </header>
        <payload>BMJc</payload>
    </encrypted>
    <request xmlns='urn:xmpp:receipts'/>
    <markable xmlns='urn:xmpp:chat-markers:0'/>
    <origin-id xmlns='urn:xmpp:sid:0' id='26338626-82b7-48f1-8951-5ce7b9c49d99'/>
    <store xmlns='urn:xmpp:hints'/>
    <encryption namespace='eu.siacs.conversations.axolotl' xmlns='urn:xmpp:eme:0' name='OMEMO'/>
</message>
```

# 音视频

## 发起语音请求

```xml

<message to='18910221510@meet.chuanshaninfo.com' id='ac091cd9051327e44313eeee827f221f604788870000003a' type='chat'
         from='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' xmlns='jabber:client'>
    <thread>glooxac091cd9051327e44313eeee827f221f6047888700000013</thread>
    <propose xmlns='urn:xmpp:jingle-message:0' id='1682520421678'>
        <description xmlns='urn:xmpp:jingle:apps:rtp:1' media='audio'/>
    </propose>
</message>
```

## 其他终端接收
```xml

<message type='chat' to='on1qv1afqmap@meet.chuanshaninfo.com'
         from='on1qv1afqmap@meet.chuanshaninfo.com/OkMSG[85b372e].M_At'>
    <accept xmlns='urn:xmpp:jingle-message:0' id='1708233185202'/>
    <store xmlns='urn:xmpp:hints'/>
</message>
```
# 发起语音初始化

```xml

<iq to='18001278080@meet.chuanshaninfo.com/monocles chat[1.5.13].5nGY'
    id='cc343947a759a05b064e97234247355e0bc4471a0000004d' type='set'
    from='18910221510@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' xmlns='jabber:client'>
    <jingle xmlns='urn:xmpp:jingle:1' action='session-initiate'
            initiator='18910221510@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' sid='1682849551882'>
        <content creator='initiator' disposition='session' name='0' senders='both'>
            <description xmlns='urn:xmpp:jingle:apps:rtp:1' media='audio'>
                <payload-type id='111' name='opus' clockrate='48000' channels='2'>
                    <rtcp-fb xmlns='urn:xmpp:jingle:apps:rtp:rtcp-fb:0' type='transport-cc'/>
                </payload-type>
                <payload-type id='63' name='red' clockrate='48000' channels='2'/>
                <payload-type id='9' name='G722' clockrate='8000'/>
                <payload-type id='102' name='ILBC' clockrate='8000'/>
                <payload-type id='0' name='PCMU' clockrate='8000'/>
                <payload-type id='8' name='PCMA' clockrate='8000'/>
                <payload-type id='13' name='CN' clockrate='8000'/>
                <payload-type id='110' name='telephone-event' clockrate='48000'/>
                <payload-type id='126' name='telephone-event' clockrate='8000'/>
                <rtp-hdrext xmlns='urn:xmpp:jingle:apps:rtp:rtp-hdrext:0' id='1'
                            uri='urn:ietf:params:rtp-hdrext:ssrc-audio-level'/>
                <rtp-hdrext xmlns='urn:xmpp:jingle:apps:rtp:rtp-hdrext:0' id='2'
                            uri='http://www.webrtc.org/experiments/rtp-hdrext/abs-send-time'/>
                <rtp-hdrext xmlns='urn:xmpp:jingle:apps:rtp:rtp-hdrext:0' id='3'
                            uri='http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01'/>
                <rtp-hdrext xmlns='urn:xmpp:jingle:apps:rtp:rtp-hdrext:0' id='4'
                            uri='urn:ietf:params:rtp-hdrext:sdes:mid'/>
                <source xmlns='urn:xmpp:jingle:apps:rtp:ssma:0' ssrc='86964338'>
                    <parameter name='cname' value='Kqv1MLGWczS2Szoh'/>
                    <parameter name='msid' value='okedu-audio-id -'/>
                    <parameter name='mslabel' value='okedu-audio-id'/>
                    <parameter name='label' value='-'/>
                </source>
                <ssrc-group xmlns='urn:xmpp:jingle:apps:rtp:ssma:0' semantics='FID'>
                    <source ssrc='86964338'/>
                </ssrc-group>
                <rtcp-mux/>
            </description>
            <transport xmlns='urn:xmpp:jingle:transports:ice-udp:1' pwd='C7YJlMw+Sh3NFeyKOz2dJfGS' ufrag='1Z9v'>
                <fingerprint xmlns='urn:xmpp:jingle:apps:dtls:0' hash='sha-256' setup='actpass'>
                    5A:A3:8E:7C:75:62:43:F6:79:F6:4D:CC:73:0D:2F:98:0F:64:1D:BF:36:0B:E7:45:1F:38:63:13:30:70:65:8B
                </fingerprint>
            </transport>
        </content>
        <group xmlns='urn:xmpp:jingle:apps:grouping:0' semantics='BUNDLE'>
            <content name='0'/>
        </group>
    </jingle>
</iq>

```

## setTransportInfo

```xml

<iq type='set' id='oMgSzFGt0EAl' to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    from='18001278080@meet.chuanshaninfo.com/monocles chat[1.5.13].5nGY'>
    <jingle sid='4965c7cd476dd152639cf02675b2c2fbd0bd08e200000030'
            action='transport-info' xmlns='urn:xmpp:jingle:1'>
        <content creator='initiator' name='0'>
            <transport pwd='4F9ywNzHAIDYm58ASZV7qwjp' ufrag='3cTO' xmlns='urn:xmpp:jingle:transports:ice-udp:1'>
                <candidate ip='10.29.184.32'
                           type='host' protocol='udp' foundation='1624237078' generation='0'
                           port='46297' priority='2122129151' component='1'/>
            </transport>
        </content>
    </jingle>
</iq>

<iq type='set' id='HspH8jmt99_C' to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    from='18001278080@meet.chuanshaninfo.com/monocles chat[1.5.13].5nGY'>
<jingle sid='4965c7cd476dd152639cf02675b2c2fbd0bd08e200000030'
        action='transport-info' xmlns='urn:xmpp:jingle:1'>
    <content creator='initiator' name='0'>
        <transport pwd='4F9ywNzHAIDYm58ASZV7qwjp' ufrag='3cTO'
                   xmlns='urn:xmpp:jingle:transports:ice-udp:1'>
            <candidate ip='2408:8406:24a0:d7e8:8d4f:31c8:872b:67d1'
                       type='host' protocol='udp' foundation='1022514418' generation='0'
                       port='44868' priority='2122197247' component='1'/>
        </transport>
    </content>
</jingle>
</iq>


```

# 修改昵称

```xml

<iq type="set" id="X14cJsEeJXvH"
    from="18910221510@meet.chuanshaninfo.com/monocles chat[1.5.14].5tVT">
    <pubsub xmlns="http://jabber.org/protocol/pubsub">
        <publish node="http://jabber.org/protocol/nick">
            <item id="current">
                <nick xmlns="http://jabber.org/protocol/nick">高杰1510</nick>
            </item>
        </publish>
    </pubsub>
</iq>
```

```xml

<iq id='638afadf1ac0551047f03586b81b6820c7c4cc0600000031' type='set'
    from='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' xmlns='jabber:client'>
    <pubsub xmlns='http://jabber.org/protocol/pubsub'>
        <publish node='http://jabber.org/protocol/nick'>
            <item id='current'>
                <nick xmlns='http://jabber.org/protocol/nick'>1851024881011</nick>
            </item>
        </publish>
    </pubsub>
</iq>

```

# 创建会议

> 请求

```xml

<body rid='2576793214'
      xmlns='http://jabber.org/protocol/httpbind'
      sid='6c659cd5-0b23-4868-92e4-79ac286f31e5'>
    <iq to='focus.meet.chuanshaninfo.com'
        type='set'
        xmlns='jabber:client'
        id='73aa5505-db99-4fdb-b9aa-90242f8591fc:sendIQ'>
        <conference xmlns='http://jitsi.org/protocol/focus'
                    room='10001@conference.meet.chuanshaninfo.com'
                    machine-uid='4246372528e41bc9b8b133a4a87f0670'>
            <property name='disableRtx' value='false'/>
            <property name='enableLipSync' value='true'/>
            <property name='openSctp' value='true'/>
        </conference>
    </iq>
</body>
```

> 返回结果

```xml

<body xmlns:stream='http://etherx.jabber.org/streams' sid='41c91036-a210-4316-bf33-13a184838d40'
      xmlns='http://jabber.org/protocol/httpbind'>
    <iq type='result' from='focus.meet.chuanshaninfo.com' xmlns='jabber:client'
        to='18510248810@meet.chuanshaninfo.com/A-sqnM4e' id='71153a3a-755e-430b-8f07-8cc8d0e28c57:sendIQ'>
        <conference room='10001@conference.meet.chuanshaninfo.com'
                    ready='true'
                    focusjid='focus@auth.meet.chuanshaninfo.com'
                    xmlns='http://jitsi.org/protocol/focus'>
            <property name='authentication' value='false'/>
        </conference>
    </iq>
</body>
```

# 开启视频

> 请求

```xml

<body rid='1702442171'
      xmlns='http://jabber.org/protocol/httpbind'
      sid='41c91036-a210-4316-bf33-13a184838d40'>
    <presence to='10001@conference.meet.chuanshaninfo.com/18510248810-7389af'
              xmlns='jabber:client'>
        <x xmlns='http://jabber.org/protocol/muc'/>
        <videomuted xmlns='http://jitsi.org/jitmeet/video'>false</videomuted>
        <c xmlns='http://jabber.org/protocol/caps' hash='sha-1'
           node='http://jitsi.org/jitsimeet' ver='vehxP5PJ8h3VqJY2hcg2uVxps00='/>
    </presence>
</body>
```

> 返回

```xml

<body xmlns:stream='http://etherx.jabber.org/streams'
      sid='41c91036-a210-4316-bf33-13a184838d40'
      xmlns='http://jabber.org/protocol/httpbind'>
    <presence xmlns='jabber:client' id='LMLDt-2622494'
              to='18510248810@meet.chuanshaninfo.com/A-sqnM4e'
              from='10001@conference.meet.chuanshaninfo.com/focus'>
        <etherpad xmlns='http://jitsi.org/jitmeet/etherpad'>10001</etherpad>
        <versions xmlns='http://jitsi.org/jitmeet'>
            <component name='focus'>1.0.692-hf</component>
        </versions>
        <conference-properties xmlns='http://jitsi.org/protocol/focus'>
            <property key='support-terminate-restart' value='true'/>
            <property key='created-ms' value='1674859993608'/>
        </conference-properties>
        <c hash='sha-1' node='http://jitsi.org/jicofo' ver='6dKlNV2hTmKYwGcTHveFMk15Ydg='
           xmlns='http://jabber.org/protocol/caps'/>
        <x xmlns='vcard-temp:x:update'>
            <photo/>
        </x>
        <x xmlns='http://jabber.org/protocol/muc#user'>
            <item role='moderator' jid='focus@auth.meet.chuanshaninfo.com/focus30994358825966944' affiliation='owner'/>
        </x>
    </presence>
    <presence xmlns='jabber:client' to='18510248810@meet.chuanshaninfo.com/A-sqnM4e'
              from='10001@conference.meet.chuanshaninfo.com/18510248810-7389af'>
        <videomuted xmlns='http://jitsi.org/jitmeet/video'>false</videomuted>
        <c hash='sha-1' node='http://jitsi.org/jitsimeet' ver='vehxP5PJ8h3VqJY2hcg2uVxps00='
           xmlns='http://jabber.org/protocol/caps'/>
        <x xmlns='vcard-temp:x:update'>
            <photo>f8edc9c6c2e61fb11544c5d7ea0ff06a77c01c9a</photo>
        </x>
        <x xmlns='http://jabber.org/protocol/muc#user'>
            <status code='100'/>
            <item role='participant' jid='18510248810@meet.chuanshaninfo.com/A-sqnM4e'
                  affiliation='none'/>
            <status code='110'/>
        </x>
    </presence>
    <message xmlns='jabber:client' to='18510248810@meet.chuanshaninfo.com/A-sqnM4e'
             from='conferenceduration.meet.chuanshaninfo.com'>
        <json-message xmlns='http://jitsi.org/jitmeet'>
            {&quot;type&quot;:&quot;conference_duration&quot;,&quot;created_timestamp&quot;:1674859994000}
        </json-message>
    </message>
    <message xmlns='jabber:client' to='18510248810@meet.chuanshaninfo.com/A-sqnM4e'
             type='groupchat' from='10001@conference.meet.chuanshaninfo.com'>
        <subject/>
    </message>
</body>
```

# 发送功能

```xml

<iq to='b6324927@conference.meet.chuanshaninfo.com/focus'
    from='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    id='MTg1MTAyNDg4MTBAbWVldC5jaHVhbnNoYW5pbmZvLmNvbS9Pa0VEVS1DbGFzc3Jvb20tRGVza3RvcABEcDF0bi0xNTcyMTQAabXO5rO1iY8lKvnWl13j3Q=='
    type='result' xmlns='jabber:client'>
    <query xmlns='http://jabber.org/protocol/disco#info' node='http://camaya.net/gloox#jAd8aCB3fxsVpqd04u5x3E9pRoU='>
        <identity category='client' type='com.chuanshaninfo.okedu-classroom-desktop'/>
        <feature var='http://jabber.org/protocol/caps'/>
        <feature var='http://jabber.org/protocol/chatstates'/>
        <feature var='http://jabber.org/protocol/disco#info'/>
        <feature var='http://jabber.org/protocol/disco#info'/>
        <feature var='http://jabber.org/protocol/disco#items'/>
        <feature var='http://jabber.org/protocol/disco#items'/>
        <feature var='http://jabber.org/protocol/disco#publish'/>
        <feature var='http://jabber.org/protocol/muc'/>
        <feature var='http://jabber.org/protocol/muc#admin'/>
        <feature var='http://jabber.org/protocol/muc#owner'/>
        <feature var='http://jabber.org/protocol/muc#request'/>
        <feature var='http://jabber.org/protocol/muc#roominfo'/>
        <feature var='http://jabber.org/protocol/muc#rooms'/>
        <feature var='http://jabber.org/protocol/muc#unique'/>
        <feature var='http://jabber.org/protocol/muc#user'/>
        <feature var='http://jabber.org/protocol/nick'/>
        <feature var='http://jabber.org/protocol/pubsub'/>
        <feature var='http://jabber.org/protocol/pubsub#auto-create'/>
        <feature var='http://jabber.org/protocol/pubsub#auto-subscribe'/>
        <feature var='http://jabber.org/protocol/pubsub#event'/>
        <feature var='http://jabber.org/protocol/pubsub#owner'/>
        <feature var='http://jabber.org/protocol/pubsub#publish-options'/>
        <feature var='http://jitsi.org/protocol/focus'/>
        <feature var='http://jitsi.org/protocol/focus'/>
        <feature var='jabber:iq:private'/>
        <feature var='jabber:iq:version'/>
        <feature var='roster:delimiter'/>
        <feature var='storage:bookmarks'/>
        <feature var='storage:rosternotes'/>
        <feature var='urn:xmpp:jingle-message:0'/>
        <feature var='urn:xmpp:jingle:1'/>
        <feature var='urn:xmpp:jingle:1'/>
        <feature var='urn:xmpp:jingle:apps:dtls:0'/>
        <feature var='urn:xmpp:jingle:apps:grouping:0'/>
        <feature var='urn:xmpp:jingle:apps:grouping:0'/>
        <feature var='urn:xmpp:jingle:apps:rtp:1'/>
        <feature var='urn:xmpp:jingle:apps:rtp:1'/>
        <feature var='urn:xmpp:jingle:apps:rtp:audio'/>
        <feature var='urn:xmpp:jingle:apps:rtp:rtcp-fb:0'/>
        <feature var='urn:xmpp:jingle:apps:rtp:rtp-hdrext:0'/>
        <feature var='urn:xmpp:jingle:apps:rtp:ssma:0'/>
        <feature var='urn:xmpp:jingle:apps:rtp:ssma:0'/>
        <feature var='urn:xmpp:jingle:apps:rtp:video'/>
        <feature var='urn:xmpp:jingle:errors:1'/>
        <feature var='urn:xmpp:jingle:transports:ice-udp:1'/>
        <feature var='urn:xmpp:jingle:transports:ice-udp:1'/>
        <feature var='urn:xmpp:ping'/>
        <feature var='urn:xmpp:ping'/>
        <feature var='vcard-temp'/>
    </query>
</iq>
```

## 群聊信息

```xml

<iq type='result' from='test5@conference.meet.chuanshaninfo.com'
    to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    id='dd2563b648620b8da55211c08e23c82e7584c38100000017'>
    <query xmlns='http://jabber.org/protocol/disco#info' node=''>
        <feature var='muc_semianonymous'/>
        <feature var='muc_public'/>
        <feature var='http://jabber.org/protocol/muc#request'/>
        <feature var='muc_open'/>
        <feature var='muc_unsecured'/>
        <feature var='muc_unmoderated'/>
        <feature var='jabber:iq:register'/>
        <feature var='muc_persistent'/>
        <feature var='http://jabber.org/protocol/muc'/>
        <feature var='http://jabber.org/protocol/muc#stable_id'/>
        <feature var='http://jabber.org/protocol/muc#self-ping-optimization'/>
        <identity name='test5' category='conference' type='text'/>
        <x xmlns='jabber:x:data' type='result'>
            <field var='FORM_TYPE' type='hidden'>
                <value>http://jabber.org/protocol/muc#roominfo</value>
            </field>
            <field var='muc#roominfo_changesubject' type='boolean'/>
            <field var='muc#roominfo_description' label='Description' type='text-single'>
                <value/>
            </field>
            <field var='{http://prosody.im/protocol/muc}roomconfig_allowmemberinvites'
                   label='Allow members to invite new members' type='boolean'>
                <value>0</value>
            </field>
            <field var='muc#roominfo_meetingId' label='The meeting unique id.' type='text-single'>
                <value>3be7067c-f41e-4b45-9b0f-938d4806f33d</value>
            </field>
            <field var='muc#roominfo_occupants' label='Number of occupants' type='text-single'>
                <value>3</value>
            </field>
            <field var='muc#roominfo_lang' type='text-single'>
                <value/>
            </field>
            <field var='muc#roomconfig_roomname' label='Title' type='text-single'/>
        </x>
    </query>
</iq>
```

## requestRoomInfo

```xml

<iq type='result' from='test@conference.meet.chuanshaninfo.com'
    to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    id='f006845e96ba71b8c686f10c0302bf4ba0dcecbe0000005a'>
    <query xmlns='http://jabber.org/protocol/muc#owner'>
        <x xmlns='jabber:x:data' type='form'>
            <title>Configuration for test@conference.meet.chuanshaninfo.com</title>
            <instructions>Complete and submit this form to configure the room.</instructions>
            <field var='FORM_TYPE' type='hidden'>
                <value>http://jabber.org/protocol/muc#roomconfig</value>
            </field>
            <field type='fixed'>
                <value>Room information</value>
            </field>
            <field var='muc#roomconfig_roomname' label='Title' type='text-single'/>
            <field var='muc#roomconfig_roomdesc' label='Description' type='text-single'>
                <desc>A brief description of the room</desc>
                <value/>
            </field>
            <field var='muc#roomconfig_lang'
                   label='Language tag for room (e.g. &apos;en&apos;, &apos;de&apos;, &apos;fr&apos; etc.)'
                   type='text-single'>
                <desc>Indicate the primary language spoken in this room</desc>
                <value/>
            </field>
            <field var='muc#roomconfig_persistentroom' label='Persistent (room should remain even when it is empty)'
                   type='boolean'>
                <desc>Rooms are automatically deleted when they are empty, unless this option is enabled</desc>
                <value>1</value>
            </field>
            <field var='muc#roomconfig_publicroom' label='Include room information in public lists' type='boolean'>
                <desc>Enable this to allow people to find the room</desc>
                <value>1</value>
            </field>
            <field type='fixed'>
                <value>Access to the room</value>
            </field>
            <field var='muc#roomconfig_roomsecret' label='Password' type='text-private'>
                <value/>
            </field>
            <field var='muc#roomconfig_membersonly' label='Only allow members to join' type='boolean'>
                <desc>Enable this to only allow access for room owners, admins and members</desc>
            </field>
            <field var='{http://prosody.im/protocol/muc}roomconfig_allowmemberinvites'
                   label='Allow members to invite new members' type='boolean'/>
            <field var='muc#roominfo_meetingId' label='The meeting unique id.' type='text-single'>
                <value>c57447e9-8026-410a-878a-706540f63927</value>
            </field>
            <field type='fixed'>
                <value>Permissions in the room</value>
            </field>
            <field var='muc#roomconfig_changesubject' label='Allow anyone to set the room&apos;s subject'
                   type='boolean'>
                <desc>Choose whether anyone, or only moderators, may set the room&apos;s subject</desc>
            </field>
            <field var='muc#roomconfig_moderatedroom' label='Moderated (require permission to speak)' type='boolean'>
                <desc>In moderated rooms occupants must be given permission to speak by a room moderator</desc>
            </field>
            <field var='muc#roomconfig_whois' label='Addresses (JIDs) of room occupants may be viewed by:'
                   type='list-single'>
                <option label='Moderators only'>
                    <value>moderators</value>
                </option>
                <option label='Anyone'>
                    <value>anyone</value>
                </option>
                <value>moderators</value>
            </field>
            <field type='fixed'>
                <value>Other options</value>
            </field>
            <field var='muc#roomconfig_historylength' label='Maximum number of history messages returned by room'
                   type='text-single'>
                <desc>Specify the maximum number of previous messages that should be sent to users when they join the
                    room
                </desc>
                <value>20</value>
            </field>
            <field var='muc#roomconfig_defaulthistorymessages'
                   label='Default number of history messages returned by room' type='text-single'>
                <desc>Specify the number of previous messages sent to new users when they join the room</desc>
                <value>20</value>
            </field>
        </x>
    </query>
</iq>

```

## 修改聊天室信息

```xml

<iq type="set" id="ozxQpd3mXkbS" from="13975412395@meet.chuanshaninfo.com/monocles chat[1.5.14].GL3J"
    to="test7@conference.meet.chuanshaninfo.com">
    <query xmlns="http://jabber.org/protocol/muc#owner">
        <x type="submit" xmlns="jabber:x:data">
            <title xmlns="jabber:x:data">Configuration for test7@conference.meet.chuanshaninfo.com</title>
            <field var="FORM_TYPE" type="hidden" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">http://jabber.org/protocol/muc#roomconfig</value>
            </field>
            <field type="fixed" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">Room information</value>
            </field>
            <field var="muc#roomconfig_roomname" label="Title" type="text-single" xmlns="jabber:x:data">
                <value>test8y</value>
            </field>
            <field var="muc#roomconfig_roomdesc" label="Description" type="text-single" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data"/>
            </field>
            <field var="muc#roomconfig_lang"
                   label="Language tag for room (e.g. &apos;en&apos;, &apos;de&apos;, &apos;fr&apos; etc.)"
                   type="text-single" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data"/>
            </field>
            <field var="muc#roomconfig_persistentroom" label="Persistent (room should remain even when it is empty)"
                   type="boolean" xmlns="jabber:x:data">
                <value>1</value>
            </field>
            <field var="muc#roomconfig_publicroom" label="Include room information in public lists" type="boolean"
                   xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">1</value>
            </field>
            <field type="fixed" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">Access to the room</value>
            </field>
            <field var="muc#roomconfig_roomsecret" label="Password" type="text-private" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data"/>
            </field>
            <field var="muc#roominfo_meetingId" label="The meeting unique id." type="text-single" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">c09861d3-5c01-4b38-a9df-2286b6e6ff8a</value>
            </field>
            <field var="muc#roomconfig_membersonly" label="Only allow members to join" type="boolean"
                   xmlns="jabber:x:data"/>
            <field var="{http://prosody.im/protocol/muc}roomconfig_allowmemberinvites"
                   label="Allow members to invite new members" type="boolean" xmlns="jabber:x:data"/>
            <field type="fixed" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">Permissions in the room</value>
            </field>
            <field var="muc#roomconfig_changesubject" label="Allow anyone to set the room&apos;s subject" type="boolean"
                   xmlns="jabber:x:data"/>
            <field var="muc#roomconfig_moderatedroom" label="Moderated (require permission to speak)" type="boolean"
                   xmlns="jabber:x:data"/>
            <field var="muc#roomconfig_whois" label="Addresses (JIDs) of room occupants may be viewed by:"
                   type="list-single" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">moderators</value>
            </field>
            <field type="fixed" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">Other options</value>
            </field>
            <field var="muc#roomconfig_historylength" label="Maximum number of history messages returned by room"
                   type="text-single" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">20</value>
            </field>
            <field var="muc#roomconfig_defaulthistorymessages"
                   label="Default number of history messages returned by room" type="text-single" xmlns="jabber:x:data">
                <value xmlns="jabber:x:data">20</value>
            </field>
        </x>
    </query>
</iq>
```

```xml

<iq to='test@conference.meet.chuanshaninfo.com' id='74e09afe1a63a172780bdff22d1f325f95c5ec3100000022' type='set'
    from='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' xmlns='jabber:client'>
    <query xmlns='http://jabber.org/protocol/muc#owner'>
        <x xmlns='jabber:x:data' type='submit'>
            <title>Configuration for test@conference.meet.chuanshaninfo.com</title>
            <instructions>Complete and submit this form to configure the room.</instructions>
            <field type='hidden' var='FORM_TYPE'>
                <value>http://jabber.org/protocol/muc#roomconfig</value>
            </field>
            <field type='fixed'>
                <value>Room information</value>
            </field>
            <field type='text-single' var='muc#roomconfig_roomname' label='Title'>
                <value>哦哦二哈哈哈er</value>
            </field>
            <field type='text-single' var='muc#roomconfig_roomdesc' label='Description'>
                <desc>A brief description of the room</desc>
                <value/>
            </field>
            <field type='text-single' var='muc#roomconfig_lang'
                   label='Language tag for room (e.g. &apos;en&apos;, &apos;de&apos;, &apos;fr&apos; etc.)'>
                <desc>Indicate the primary language spoken in this room</desc>
                <value/>
            </field>
            <field type='boolean' var='muc#roomconfig_persistentroom'
                   label='Persistent (room should remain even when it is empty)'>
                <desc>Rooms are automatically deleted when they are empty, unless this option is enabled</desc>
                <value>1</value>
            </field>
            <field type='boolean' var='muc#roomconfig_publicroom' label='Include room information in public lists'>
                <desc>Enable this to allow people to find the room</desc>
                <value>1</value>
            </field>
            <field type='fixed'>
                <value>Access to the room</value>
            </field>
            <field type='text-private' var='muc#roomconfig_roomsecret' label='Password'>
                <value/>
            </field>
            <field type='text-single' var='muc#roominfo_meetingId' label='The meeting unique id.'>
                <value>1afcbdc9-97bb-4d5e-a17a-3b8e7cb4a5a2</value>
            </field>
            <field type='boolean' var='muc#roomconfig_membersonly' label='Only allow members to join'>
                <desc>Enable this to only allow access for room owners, admins and members</desc>
                <value>0</value>
            </field>
            <field type='boolean' var='{http://prosody.im/protocol/muc}roomconfig_allowmemberinvites'
                   label='Allow members to invite new members'>
                <value>0</value>
            </field>
            <field type='fixed'>
                <value>Permissions in the room</value>
            </field>
            <field type='boolean' var='muc#roomconfig_changesubject'
                   label='Allow anyone to set the room&apos;s subject'>
                <desc>Choose whether anyone, or only moderators, may set the room&apos;s subject</desc>
                <value>0</value>
            </field>
            <field type='boolean' var='muc#roomconfig_moderatedroom' label='Moderated (require permission to speak)'>
                <desc>In moderated rooms occupants must be given permission to speak by a room moderator</desc>
                <value>0</value>
            </field>
            <field type='list-single' var='muc#roomconfig_whois'
                   label='Addresses (JIDs) of room occupants may be viewed by:'>
                <option label='Anyone'>
                    <value>anyone</value>
                </option>
                <option label='Moderators only'>
                    <value>moderators</value>
                </option>
                <value>moderators</value>
            </field>
            <field type='fixed'>
                <value>Other options</value>
            </field>
            <field type='text-single' var='muc#roomconfig_historylength'
                   label='Maximum number of history messages returned by room'>
                <desc>Specify the maximum number of previous messages that should be sent to users when they join the
                    room
                </desc>
                <value>20</value>
            </field>
            <field type='text-single' var='muc#roomconfig_defaulthistorymessages'
                   label='Default number of history messages returned by room'>
                <desc>Specify the number of previous messages sent to new users when they join the room</desc>
                <value>20</value>
            </field>
            <field type='text-single' var='muc#roomconfig_roomname' label='Title'>
                <value>哦哦二哈哈哈er8</value>
            </field>
        </x>
    </query>
</iq>

```

# 文件
## 请求（file-transfer:3）
> https://xmpp.org/extensions/attic/xep-0234-0.14.html
```xml
<iq id='9mIqudPbaFOB' to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    from='18001278080@meet.chuanshaninfo.com/monocles chat[1.5.13].5nGY' type='set'>
    <jingle action='session-initiate' sid='IIKW3cq76AqOulj6YUTWRg' xmlns='urn:xmpp:jingle:1'>
        <content senders='initiator' name='y5HsPrmglOY6TGytEhkE1Q' creator='initiator'>
            <description xmlns='urn:xmpp:jingle:apps:file-transfer:3'>
                <offer>
                    <file>
                        <date>1969-07-21T02:56:15Z</date>
                        <desc>This is a test. If this were a real file...</desc>
                        <name>test.txt</name>
                        <range/>
                        <size>1022</size>
                        <hashes xmlns='urn:xmpp:hashes:0'>
                            <hash algo='sha1'>552da749930852c69ae5d2141d3766b1</hash>
                        </hashes>
                    </file>
                </offer>
            </description>
            <transport xmlns='urn:xmpp:jingle:transports:ibb:1'
                       sid='k9XnltRw/0YxyC2sq6pjdQ'
                       block-size='8192'/>
        </content>
    </jingle>
</iq>

```
## 请求（urn:xmpp:jingle:apps:file-transfer:4）
> https://xmpp.org/extensions/attic/xep-0234-0.16.html
```xml
<iq from='romeo@montague.lit/orchard'
    id='nzu25s8'
    to='juliet@capulet.lit/balcony'
    type='set'>
    <jingle xmlns='urn:xmpp:jingle:1'
            action='session-initiate'
            initiator='romeo@montague.lit/orchard'
            sid='851ba2'>
        <content creator='initiator' name='a-file-offer'>
            <description xmlns='urn:xmpp:jingle:apps:file-transfer:4'>
                <file>
                    <date>1969-07-21T02:56:15Z</date>
                    <desc>This is a test. If this were a real file...</desc>
                    <media-type>text/plain</media-type>
                    <name>test.txt</name>
                    <range/>
                    <size>1022</size>
                    <hash xmlns='urn:xmpp:hashes:1' algo='sha-1'>552da749930852c69ae5d2141d3766b1</hash>
                </file>
            </description>
            <transport xmlns='urn:xmpp:jingle:transports:s5b:1'
                       mode='tcp'
                       sid='vj3hs98y'>
                <candidate cid='hft54dqy'
                           host='192.168.4.1'
                           jid='romeo@montague.lit/orchard'
                           port='5086'
                           priority='8257636'
                           type='direct'/>
                <candidate cid='hutr46fe'
                           host='24.24.24.1'
                           jid='romeo@montague.lit/orchard'
                           port='5087'
                           priority='8258636'
                           type='direct'/>
            </transport>
        </content>
    </jingle>
</iq>

```
## 请求（urn:xmpp:jingle:apps:file-transfer:5）
> https://xmpp.org/extensions/attic/xep-0234-0.19.1.html
```xml
<iq type='set' id='J1SqwzjJWXs1' from='on1qv1afqmap@meet.chuanshaninfo.com/OkMSG[85b372e].uZj_'
    to='jidlpdyibulw@meet.chuanshaninfo.com/OkEDU[v1.3.0-231231-14-ga1fdca6].OWVjYj'>
    <jingle xmlns='urn:xmpp:jingle:1' sid='4SvSAzONnqytdR1TKD4wAg' action='session-initiate'>
        <content name='NQHQC6QtvLL/o7QusX509Q' creator='initiator' senders='initiator'>
            <description xmlns='urn:xmpp:jingle:apps:file-transfer:5'>
                <file>
                    <date>1969-07-21T02:56:15Z</date>
                    <desc>This is a test. If this were a real file...</desc>
                    <media-type>text/plain</media-type>
                    <name>test.txt</name>
                    <range/>
                    <size>6144</size>
                    <hash xmlns='urn:xmpp:hashes:2'
                          algo='sha-1'>w0mcJylzCn+AfvuGdqkty2+KP48=</hash>
                </file> 
            </description>
            <transport xmlns='urn:xmpp:jingle:transports:ibb:1' sid='i+BJuj3cyluPHEsSd+EqpQ' block-size='8192'/>
        </content>
    </jingle>
</iq>
```
```xml

<iq to='13661358184@meet.chuanshaninfo.com/monocles chat[1.5.14].Uf7P'
    id='5dc46f3c60a99a26afb9c9d7440e49e9295ef7e500000036' type='set'
    from='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' xmlns='jabber:client'>
    <jingle xmlns='urn:xmpp:jingle:1' action='session-initiate'
            initiator='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
            sid='5dc46f3c60a99a26afb9c9d7440e49e9295ef7e500000035'>
        <description xmlns='urn:xmpp:jingle:apps:file-transfer:3'>
            <offer>
                <file>
                    <date/>
                    <name>replay_pid4573.log</name>
                    <desc/>
                    <size>2695864</size>
                    <range offset='-1'/>
                </file>
            </offer>
        </description>
        <transport xmlns='urn:xmpp:jingle:transports:ibb:1' sid='replay_pid4573.log' block-size='4096'/>
    </jingle>
</iq>

```

## 接受

```xml

<iq to='18001278080@meet.chuanshaninfo.com/monocles chat[1.5.13].5nGY'
    id='22cf03d7a7b878f8ec6f34e6e7b0a8c31a6a7e8700000035' type='set'
    from='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' xmlns='jabber:client'>
    <jingle xmlns='urn:xmpp:jingle:1' action='session-accept'
            responder='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop' sid='7dDod5iRvni2ZXyRs2tiig'>
        <content creator='initiator' disposition='session' name='file' senders='both'>
            <description xmlns='urn:xmpp:jingle:apps:file-transfer:3'>
                <request>
                    <file>
                        <date/>
                        <name>OIP-C.jpg</name>
                        <desc/>
                        <size>31026</size>
                        <range offset='-1'/>
                    </file>
                </request>
            </description>
            <transport xmlns='urn:xmpp:jingle:transports:ibb:1' sid='wmEBp4Xszb7WbkfPMLeI2w' block-size='8192'/>
        </content>
    </jingle>
</iq>


```

## 开启流

```xml

<iq id='k3A0O_3CYZ98'
    to='18510248810@meet.chuanshaninfo.com/OkEDU-Classroom-Desktop'
    type='set'
    from='13661358184@meet.chuanshaninfo.com/monocles chat[1.5.14].Uf7P'>
    <open sid='dPrnJ2Zut5tNB12ucxEHQw'
          xmlns='http://jabber.org/protocol/ibb'
          stanza='iq'
          block-size='8192'/>
</iq>


```

# 群聊
## 信息
```xml
<iq type='result' id='a02cecf19178ab484c754e6911cf1b1d0e48258300000018' from='support@conference.meet.chuanshaninfo.com' to='jidlpdyibulw@meet.chuanshaninfo.com/OkEDU[v1.3.0-231231-14-ga1fdca6].OWVjYj'>
   
   <query xmlns='http://jabber.org/protocol/disco#info'>
       <identity category='conference' name='技术支持' type='text'/>
       <feature var='http://jabber.org/protocol/muc'/>
       <feature var='muc_public'/>
       <feature var='muc_open'/>
       <feature var='muc_unmoderated'/>
       <feature var='muc_nonanonymous'/>
       <feature var='muc_unsecured'/>
       <feature var='muc_persistent'/>
       <feature var='http://jabber.org/protocol/muc#self-ping-optimization'/>
       <feature var='vcard-temp'/>
       <feature var='urn:xmpp:sid:0'/>
       <feature var='http://jabber.org/protocol/disco#info'/>
       <feature var='urn:xmpp:bookmarks-conversion:0'/>
       
       <x xmlns='jabber:x:data' type='result'>
           <field var='FORM_TYPE' type='hidden'>
               <value>http://jabber.org/protocol/muc#roominfo</value>
           </field>
           <field var='muc#roominfo_description' type='text-single' label='描述'>
               <value>问题反馈与交流</value>
           </field>
           <field var='muc#roominfo_subject' type='text-single' label='主题'>
               <value/>
           </field>
           <field var='muc#roominfo_occupants' type='text-single' label='成员人数'>
               <value>2</value>
           </field>
           <field var='x-muc#roominfo_creationdate' type='text-single' label='创建日期'>
               <value>2024-02-07T09:12:34.474Z</value>
           </field>
       </x>
   </query>
</iq>
```

# Carbons
```xml

<message type='chat' from='on1qv1afqmap@meet.chuanshaninfo.com'
         to='on1qv1afqmap@meet.chuanshaninfo.com/OkEDU[v1.3.0-231231-37-g0faec8d].OWVjYj'>
    <sent xmlns='urn:xmpp:carbons:2'>
        <forwarded xmlns='urn:xmpp:forward:0'>
            <message xmlns='jabber:client' type='chat'
                     to='jidlpdyibulw@meet.chuanshaninfo.com/OkEDU[v1.3.0-231231-39-g6f666def].NDc5MD'
                     from='on1qv1afqmap@meet.chuanshaninfo.com/OkMSG[85b3'>
                <reject xmlns='urn:xmpp:jingle-message:0' id='1708231445174'/>
                <store xmlns='urn:xmpp:hints'/>
            </message>
        </forwarded>
    </sent>
</message>
```