# sdauKillMonster
农大斩妖传
基于Cocos2dx引擎开发，，好像版本是3.x，，年代比较久远了，15年初，好像是大二的时候开发的一款mmrpg手机小游戏

游戏运行效果图

![图片1](https://raw.githubusercontent.com/butyfrombupt/sdauKillMonster/master/jpg/%E5%9B%BE%E7%89%871.png)

![图片2](https://raw.githubusercontent.com/butyfrombupt/sdauKillMonster/master/jpg/%E5%9B%BE%E7%89%872.png)

![图片3](https://raw.githubusercontent.com/butyfrombupt/sdauKillMonster/master/jpg/%E5%9B%BE%E7%89%873.png)

![图片4](https://raw.githubusercontent.com/butyfrombupt/sdauKillMonster/master/jpg/%E5%9B%BE%E7%89%874.png)

![图片5](https://raw.githubusercontent.com/butyfrombupt/sdauKillMonster/master/jpg/%E5%9B%BE%E7%89%875.png)

![图片6](https://raw.githubusercontent.com/butyfrombupt/sdauKillMonster/master/jpg/%E5%9B%BE%E7%89%876.png)

![图片7](https://raw.githubusercontent.com/butyfrombupt/sdauKillMonster/master/jpg/%E5%9B%BE%E7%89%877.png)

任务对话动图：
![动图1](https://github.com/butyfrombupt/sdauKillMonster/blob/master/jpg/%E6%BC%94%E7%A4%BA%E8%A7%86%E9%A2%91%20(1).gif)

最后的Boss战斗动图
这个Boss的参考模型是Dota中的影魔 0.0
![动图2](https://github.com/butyfrombupt/sdauKillMonster/blob/master/jpg/%E6%BC%94%E7%A4%BA%E8%A7%86%E9%A2%91.gif)


使用了CocosStudio做了游戏的开始界面和选人界面，因为这两个页面的绑定代码的部分比较少，而且为了使游戏能给人以眼前一亮的感觉，我们就用CocosStudio先把静态界面做好，其中使用到的资源都是我们的美工自己绘制加上使用Phototshop制作成的。而游戏场景中有人物的对话，我们将这一场景层抽象出来，也是用CocosStudio先将需要的三个控件摆放在合适的位置，再根据加载不同的对话动态的去读早已写在配置文件里的图片资源。除此之外，我们还用CocosStudio将人物的动画帧都做好，只需要在使用的时候调用我们命名好的动作名称。

而游戏的其他场景我们使用了TiledMap去制作，因为我们使用TiledMap可以将碰撞层加进去，这样游戏主角就可以碰到碰撞物就停止行走。我们通过触碰机制获取人物的行走方向调用写好的状态机对人物的动画进行切换。

我们的美工用电脑手绘板将人物的立绘和Q版攻击动作和行走动作以及用Phototshop对游戏场景和游戏中使用的大部分图片资源进行绘制
