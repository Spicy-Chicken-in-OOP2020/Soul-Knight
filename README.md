# Soul Knight项目说明文档
>同济大学软件学院2020年面向对象程序设计课程大项目
## 项目信息

* 项目选题：元气骑士

* 项目成员与贡献比例   

  * 1851055 汪明杰  25%
  * 1850668 李俊杰  25%
  * 1851231 王立友  25%
  * 1950509 马家昱  25%

* 项目github地址：
  <https://github.com/Spicy-Chicken-in-OOP2020/Soul-Knight>
* 项目进度时间线：
![image](https://github.com/Spicy-Chicken-in-OOP2020/Soul-Knight/blob/master/Resources/%E6%97%B6%E9%97%B4%E7%BA%BF.png)
## 项目开发文档
* 选用引擎：Cocos2d-x 3.17.2

* 辅助软件：Tiled Map Editor 1.1.5、Adobe Photoshop CC 2018

* 支持平台：Windows

* 小组分工：

  姓名    |  分工   |
  :-----|:---------------|
  汪明杰| 素材、武器类、子弹类、地刺 | 
  李俊杰| 怪物类、boss类、道具类、商店 | 
  王立友| buff与debuff、地图绘制、特殊地形、小地图 |
  马家昱| UI界面绘制、金手指、键位选择 | 

* 类的设计及继承关系
![image](https://github.com/Spicy-Chicken-in-OOP2020/Soul-Knight/blob/master/Resources/%E7%B1%BB%E7%9A%84%E7%BB%A7%E6%89%BF%E5%85%B3%E7%B3%BB.png)
### 评分项目完成度

#### 基础功能
   * [x] 游戏开始界⾯、背景⾳乐、⾳量控制、暂停及恢复功能、退出功能
   * [x] 键盘控制
   * [x] ⾄少2类武器，包括不限于枪械类武器、近战武器；每类武器⾄少包括2种具体的武器，如枪械类
   * [x] 武器包括不限于⼀次发射单发⼦弹的枪械、⼀次发射多发⼦弹枪械等，近战武器包括不限于可快速
         攻击的⼩范围武器、攻击速度较慢的⼤范围武器等
   * [x] ⾄少2种普通敌⼈类型，包括不限于近战型敌⼈和远程型敌⼈；每类普通敌⼈⾄少包括2类具体的敌⼈
   * [x] ⾄少两种道具，包括不限于恢复⽣命、增加护甲的道具，可以通过击败敌⼈获取
   * [x] 宝箱机制，开启可获得新武器或者道具等
   * [x] 安全地图与探险地图，安全地图指进⼊关卡前的地图，可以查看武器信息、敌⼈信息等，探险地图指关卡地图
   * [x] 关卡中主⻆死亡，探险终⽌并返回安全地图
   * [x] ⾄少包括2个关卡
   
#### 可选功能
   * [x] 游戏⼩地图，可以显示已经探索过的地图，可以参考元⽓骑⼠的⼩地图
   * [x] 多个可选主⻆，每个主⻆拥有不同的属性加成（近战攻击速度提升、枪械⼦弹速度提升、⽣命值增加等）或者主动技能（移速增加、翻滚躲⼦弹）
   * [x] buff机制，主⻆可以获得多种buff，包括不限于移速增加、⽆敌等
   * [x] debuff机制，主⻆会获得多种debuff，包括不限于移速减慢等
   * [x] ⾦币机制，击败敌⼈可以获取⾦币
   * [x] 主⻆等级系统，⾼等级主⻆拥有更强的属性或能⼒，主⻆可以通过消耗⾦币升级（在安全地图中）
   * [x] 安全地图中商店系统，可以在进⼊关卡前购买或抽取特殊道具、武器等
   * [x] 探险地图中的⽼爷爷系统，可以在关卡中购买/获赠礼物，如武器/道具/buff等
   * [x] 特殊地形，包括不限于可被破坏区域（如⽊墙）、移速受限区域（如沼泽）、通过受伤区域（如岩浆）、机关地形（如时不时出现的地刺）等
   * [x] BOSS型敌⼈
   * [x] 秘籍，如⼗倍攻击⼒、⽆敌等
   
#### 加分项
   * [x] 版本控制与团队协作
       * 符合⼀些 git 最佳实践（如 commit 历史⼲净规范、commit 描述规范、commit 包含且仅包含⼀项功能、使⽤ Pull Request 功能或分⽀进⾏团队          协作等）；
       * 团队成员分⼯平等、合理；
   * [x] 代码质量与安全
       * 对于复杂逻辑使⽤单元测试验证正确性；
   * [x] 功能和架构
       * 界⾯精致；
       * 项⽬⽬录结构良好、清晰；
   * [x] 合理使用的c++特性
       * 初始化列表
       * 类型推断 ( auto / decltype )
       * 基于范围的 for 循环
       * 智能指针
       * 常量表达式 ( constexpr )
       * Lambda 表达式
       * 字符串字⾯量
   * [X] 其他亮点
   	* 雕像系统，可以为主角增加buff
        * 键位选择：支持玩家选择两种不同的操作方式
        * 怪物警觉系统：角色靠近怪物时会触发怪物警觉动画，从而使其具有攻击性
        * 当敌人未被清空时，房间大门处于锁死状态
        * 武器等级系统：游戏中有NPC“铸铁匠”可以为武器升级，提升武器攻击力，减少消耗魔法值
        * 货币系统：存在游戏内金币与用户蓝币两种货币
        * 自动存档功能：角色等级与货币在退出游戏时会自动保留	
        * UI与画面精美，高度还原游戏原貌
 
 * 代码亮点
 
 * Boss向周围发射子弹
 ```
 static int cnt = 0;
	if (cnt > 1000) {
		cnt = 0;
		auto s1 = ShootController::createForBoss(CIRCULE, this);
		this->addChild(s1);
		/*缓冲*/
		for (int i = 0; i < 10000; ++i);

		/*auto s2 = ShootController::createForBoss(SQUARE, this);
		this->addChild(s2);*/
	}
	else {
		++cnt;
	}	
 ```
 
 * 障碍物判定
 
 ```
 bool Boss::isStuck(const Point& objPos) {
	/*层大小*/
	auto layerSize = _collisionLayer->getLayerSize();

	//判断是否触及障碍物
	Size mapSize = GlobalParameter::mapNow->getMapSize();
	Size tileSize = GlobalParameter::mapNow->getTileSize();

	/*转换为地图上的坐标系*/
	Point tilesPos(objPos.x / tileSize.width, (mapSize.height * tileSize.height - objPos.y) / tileSize.height);

	if (tilesPos.x < 0 || tilesPos.y < 0 || tilesPos.x >= layerSize.width || tilesPos.y >= layerSize.height) {
		log("bad ways1\n");

		return true;
	}

	/*获取地图格子的唯一表示*/
	int tiledGidcollsion = _collisionLayer->getTileGIDAt(tilesPos);
	int tiledGidcollsion1 = _collision1Layer->getTileGIDAt(tilesPos);
	int tiledGidOutside = _outsideLayer->getTileGIDAt(tilesPos);
	int tiledGidCan = _canLayer->getTileGIDAt(tilesPos);


	//图块ID不为空，表示是障碍物
	if (tiledGidcollsion != 0 || tiledGidcollsion1 != 0 || tiledGidOutside != 0 || tiledGidCan != 0) {

		log("bad ways2\n");

		return true;
	}

	return false;
}
```
* 子弹爆炸特效

```
for (int i = 1; i <= iFrameNum; i++)
	{
		std::string se = StringUtils::format("Breath_%02d.png", i);
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Breath_%02d.png", i));
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	Animate* action = Animate::create(animation);

	//创建一个回调函数
	CallFunc* callFunc = CallFunc::create(
		[&]() {
		}
	);

	//组合动作
	Action* actions = Sequence::create(action, callFunc, NULL);
```

## 游戏说明

### 游戏简介
元气骑士是一款地牢类角色扮演游戏，玩家将会在随机关卡中遇到不同的敌人，并且躲避子弹，收集金币，不断获得更强力的武器。
### 游戏玩法
进入游戏后选择要操作的人物角色，在安全地图挑选武器后进入关卡。游戏全程共有五关，走到最后击败最终Boss即可胜利通关。击杀敌人与开启宝箱可以获得武器与金币。不断升级角色，用金币购买更加强力的武器来击败敌人！
### 基本操作

  操作    |  效果   | 
  :-----|:---------------
  WASD或↑↓←→| 移动主角 
  J或Z| 攻击键 
  X或K| 交互键
  
### 角色及成长属性  

|  角色   | 生命值  | 蓝量  | 护甲  | 
|  ----  | ----  | ----  | ----  |
| 骑士  | 8/9/10/11/12 | 220/240/250/260/270 | 8/9/10/11/12 | 
| 牧师  | 7/8/9/10/11 | 240/260/280/300/320 | 8/9/10/11/12 |

### 武器

|  武器   | 类型  | 攻击力  |
|  ----  | ----  | ----  |
| 步枪  |   远程     | 3 |
| 冲锋枪  | 远程 | 2 |
| 短刀  | 近战 | 3 |
| 长刀  | 近战 | 10 |

### 敌人

|  敌人   | 类型  | 血量  | 攻击力
|  ----  | ----  | ----  | ----  |
| 持枪者  | 远程 | 10 | 1  |
| 持刀者  | 近战 | 10|  1 |
| 水晶巨蟹  | Boss | 100 | 1&3 |


### 画面概览

* 开始界面
![image](https://github.com/Spicy-Chicken-in-OOP2020/Soul-Knight/blob/master/Resources/%E6%88%AA%E5%9B%BE1.png)
* 关卡地图
![image](https://github.com/Spicy-Chicken-in-OOP2020/Soul-Knight/blob/master/Resources/%E6%88%AA%E5%9B%BE2.png)
* Boss战
![image](https://github.com/Spicy-Chicken-in-OOP2020/Soul-Knight/blob/master/Resources/%E6%88%AA%E5%9B%BE3.png)

